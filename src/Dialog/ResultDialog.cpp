#include "ResultDialog.h"
#include "FlangeConfigDialog.h"
#include "ShellFlangeConfigDialog.h"
#include "CalcResultSerializer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QFrame>
#include <QFileDialog>
#include <QMessageBox>
#include <algorithm>
#include <cmath>

ResultDialog::ResultDialog(const CalculationResult& res, QWidget* parent)
    : QDialog(parent), m_result(res)
{
    setWindowTitle("Подробные результаты расчета");
    this->setStyleSheet("QWidget { font-size: 10pt; }");

    initStandardFlanges();
    autoSelectFlange();
    autoSelectShellFlange();

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 8);

    if (!m_result.error_message.empty()) {
        auto* err = new QLabel(QString::fromStdString(m_result.error_message));
        err->setStyleSheet("font-weight: bold; color: red;");
        err->setWordWrap(true);
        mainLayout->addWidget(err);
        auto* close = new QPushButton("Закрыть");
        connect(close, &QPushButton::clicked, this, &QDialog::reject);
        mainLayout->addWidget(close);
        return;
    }

    auto* container = new QWidget();
    auto* form = new QFormLayout(container);
    form->setSpacing(8);
    form->setLabelAlignment(Qt::AlignLeft);

    addRow(form, "ТЕПЛОФИЗИКА", "", true);
    addRow(form, "Требуемая мощность:",
        QString::number(m_result.Q_required / 1000.0, 'f', 2) + " кВт");
    addRow(form, "LMTD (напор):",
        QString::number(m_result.LMTD_real, 'f', 2) + " °C");
    addRow(form, "Коэф. теплопередачи:",
        QString::number(m_result.K, 'f', 1) + " Вт/(м²·К)");
    addRowHotCold(form, "Коэф. теплоотдачи (гор/хол):",
        QString::number(m_result.alpha_hot, 'f', 1),
        QString::number(m_result.alpha_cold, 'f', 1));
    addRow(form, "Теплопроводность стенки:",
        QString::number(m_result.wall.lambda, 'f', 1) + " Вт/(м·К)");

    addRow(form, "ГИДРОДИНАМИКА", "", true);
    addRowHotCold(form, "Скорость среды (гор/хол):",
        QString::number(m_result.velocity_hot, 'f', 2),
        QString::number(m_result.velocity_cold, 'f', 2),
        "м/с");
    addRowHotCold(form, "Число Re среды (гор/хол):",
        QString::number((int)m_result.Re_hot),
        QString::number((int)m_result.Re_cold));

    addRow(form, "ГЕОМЕТРИЯ КОРПУСА", "", true);
    addRow(form, "Наружный диаметр:",
        QString::number(m_result.D * 1000.0, 'f', 1) + " мм");
    addRow(form, "Площадь поверхности:",
        QString::number(m_result.A, 'f', 2) + " м²");
    addRow(form, "Количество витков:",
        QString::number(m_result.turns, 'f', 1));
    addRowHotCold(form, "Ширина канала (гор/хол):",
        QString::number(m_result.geometry.width_hot * 1000.0, 'f', 1),
        QString::number(m_result.geometry.width_cold * 1000.0, 'f', 1),
        "мм");
    addRow(form, "Длина канала:",
        QString::number(m_result.channel_length, 'f', 2) + " м");
    addRow(form, "Ширина листа:",
        QString::number(m_result.channel_width * 1000.0, 'f', 1) + " мм");
    addRow(form, "Вн. диаметр спирали:",
        QString::number(m_result.geometry.d_inner * 1000.0, 'f', 1) + " мм");

    {
        m_coverThicknessSpin = new QDoubleSpinBox();
        m_coverThicknessSpin->setRange(5.0, 200.0);
        m_coverThicknessSpin->setDecimals(1);
        m_coverThicknessSpin->setSuffix(" мм");
        m_coverThicknessSpin->setSingleStep(1.0);
        m_coverThicknessSpin->setValue(m_result.geometry.cover_thickness * 1000.0);
        m_coverThicknessSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        m_coverThicknessSpin->setFixedWidth(90);
        form->addRow("Толщина крышки:", m_coverThicknessSpin);
    }

    {
        m_shellThicknessSpin = new QDoubleSpinBox();
        m_shellThicknessSpin->setRange(5.0, 200.0);
        m_shellThicknessSpin->setDecimals(1);
        m_shellThicknessSpin->setSuffix(" мм");
        m_shellThicknessSpin->setSingleStep(1.0);
        m_shellThicknessSpin->setValue(m_result.geometry.shell_thickness * 1000.0);
        m_shellThicknessSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        m_shellThicknessSpin->setFixedWidth(90);
        form->addRow("Толщина обечайки:", m_shellThicknessSpin);
    }

    addRow(form, "Толщина стенки листа:",
        QString::number(m_result.wall.thickness * 1000.0, 'f', 1) + " мм");

    {
        m_gasketThicknessSpin = new QDoubleSpinBox();
        m_gasketThicknessSpin->setRange(0.5, 50.0);
        m_gasketThicknessSpin->setDecimals(1);
        m_gasketThicknessSpin->setSuffix(" мм");
        m_gasketThicknessSpin->setSingleStep(0.5);
        m_gasketThicknessSpin->setValue(m_result.gasket_thickness * 1000.0);
        m_gasketThicknessSpin->setButtonSymbols(QAbstractSpinBox::NoButtons);
        m_gasketThicknessSpin->setFixedWidth(90);
        form->addRow("Толщина прокладки:", m_gasketThicknessSpin);
    }

    addRow(form, "ПАТРУБКИ И ФЛАНЦЫ", "", true);
    addRow(form, "Расчетный диаметр входного отверстия:",
        QString::number(m_result.inlet_D * 1000.0, 'f', 1) + " мм");

    {
        auto* flangeLine = new QWidget();
        auto* flangeLayout = new QHBoxLayout(flangeLine);
        flangeLayout->setContentsMargins(0, 0, 0, 0);

        m_flangeLabel = new QLabel(getFlangeSummary());
        m_flangeLabel->setStyleSheet("font-weight: 500;");

        auto* editBtn = new QPushButton("⚙");
        editBtn->setFixedSize(24, 24);
        connect(editBtn, &QPushButton::clicked, this, &ResultDialog::openFlangeEditor);

        flangeLayout->addWidget(m_flangeLabel);
        flangeLayout->addWidget(editBtn);
        flangeLayout->addStretch();
        form->addRow("Фланец патрубка:", flangeLine);
    }

    {
        auto* sfLine = new QWidget();
        auto* sfLayout = new QHBoxLayout(sfLine);
        sfLayout->setContentsMargins(0, 0, 0, 0);

        m_shellFlangeLabel = new QLabel(getShellFlangeSummary());
        m_shellFlangeLabel->setStyleSheet("font-weight: 500;");

        auto* editBtn = new QPushButton("⚙");
        editBtn->setFixedSize(24, 24);
        connect(editBtn, &QPushButton::clicked,
            this, &ResultDialog::openShellFlangeEditor);

        sfLayout->addWidget(m_shellFlangeLabel);
        sfLayout->addWidget(editBtn);
        sfLayout->addStretch();
        form->addRow("Фланец обечайки:", sfLine);
    }

    auto* scrollContent = new QWidget();
    auto* scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setContentsMargins(8, 8, 8, 8);
    scrollLayout->setSpacing(4);
    scrollLayout->addWidget(container);

    scrollLayout->addStretch();

    auto* scrollArea = new QScrollArea();
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->addWidget(scrollArea, 1);

    {
        QStringList warnings = buildWarnings();
        if (!warnings.isEmpty()) {
            auto* warnFrame = new QFrame();
            warnFrame->setFrameShape(QFrame::StyledPanel);
            warnFrame->setStyleSheet(
                "QFrame { background: #fff8e1; border: 0px solid #f9a825; border-radius: 4px; }"
                "QLabel { color: #5d4037; font-size: 9.5pt; }");

            auto* warnLayout = new QVBoxLayout(warnFrame);
            warnLayout->setContentsMargins(8, 6, 8, 6);
            warnLayout->setSpacing(3);

            auto* title = new QLabel("Обнаружены несоответствия:");
            title->setStyleSheet("font-weight: bold; color: #e65100;");
            warnLayout->addWidget(title);

            for (const QString& w : warnings) {
                auto* lbl = new QLabel("• " + w);
                lbl->setWordWrap(true);
                warnLayout->addWidget(lbl);
            }

            mainLayout->addWidget(warnFrame);
        }
    }

    auto* separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    mainLayout->addWidget(separator);

    auto* bottom = new QHBoxLayout();
    bottom->setContentsMargins(8, 0, 8, 0);
    auto* cancel = new QPushButton("Отмена");
    m_saveCalcBtn = new QPushButton("Сохранить расчёт");
    m_confirmBtn = new QPushButton("Построить модель");
    cancel->setMinimumHeight(35);
    m_saveCalcBtn->setMinimumHeight(35);
    m_confirmBtn->setMinimumHeight(35);
    m_confirmBtn->setDefault(true);

    bottom->addWidget(m_saveCalcBtn);
    bottom->addStretch();
    bottom->addWidget(cancel);
    bottom->addWidget(m_confirmBtn);
    mainLayout->addLayout(bottom);

    resize(580, 700);

    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_saveCalcBtn, &QPushButton::clicked, this, &ResultDialog::onSaveCalc);
    connect(m_confirmBtn, &QPushButton::clicked, this, [this]() {
        if (m_currentSelectedFlange)
            m_result.selected_flange = *m_currentSelectedFlange;
        if (m_currentShellFlange)
            m_result.shell_flange = *m_currentShellFlange;
        if (m_gasketThicknessSpin)
            m_result.gasket_thickness = m_gasketThicknessSpin->value() / 1000.0;
        if (m_coverThicknessSpin)
            m_result.geometry.cover_thickness = m_coverThicknessSpin->value() / 1000.0;
        if (m_shellThicknessSpin)
            m_result.geometry.shell_thickness = m_shellThicknessSpin->value() / 1000.0;

        emit selectedResultConfirmed(m_result);
        accept();
        });
}

void ResultDialog::addRow(QFormLayout* layout, const QString& label,
    const QString& value, bool isHeader)
{
    if (isHeader) {
        auto* lbl = new QLabel(label);
        lbl->setStyleSheet(
            "font-weight: bold; font-size: 11pt; "
            "margin-top: 10px; border-bottom: 2px solid palette(mid);");
        layout->addRow(lbl);
    }
    else {
        auto* val = new QLabel(value);
        val->setStyleSheet("font-weight: 500;");
        layout->addRow(new QLabel(label), val);
    }
}

void ResultDialog::addRowHotCold(QFormLayout* layout, const QString& label,
    const QString& hotValue, const QString& coldValue, const QString& suffix)
{
    QString html = QString(
        "<span style='color:#cc2200;font-weight:500'>%1</span>"
        " / "
        "<span style='color:#0055cc;font-weight:500'>%2</span>%3")
        .arg(hotValue)
        .arg(coldValue)
        .arg(suffix.isEmpty() ? QString() : " " + suffix);

    auto* val = new QLabel(html);
    val->setTextFormat(Qt::RichText);
    layout->addRow(new QLabel(label), val);
}

void ResultDialog::autoSelectFlange()
{
    double target = m_result.inlet_D * 1000.0;
    for (const auto& f : m_standardFlanges) {
        if (f.inner_d >= target) {
            m_currentSelectedFlange = f;
            return;
        }
    }
    if (!m_standardFlanges.empty())
        m_currentSelectedFlange = m_standardFlanges.front();
}

QString ResultDialog::getFlangeSummary() const
{
    if (!m_currentSelectedFlange) return "Не выбран";
    return QString("%1, s=%2 мм, L=%3 мм")
        .arg(QString::fromStdString(m_currentSelectedFlange->name))
        .arg(m_result.nozzle_shell_thickness, 0, 'f', 1)
        .arg(m_result.nozzle_shell_length, 0, 'f', 1);
}

void ResultDialog::openFlangeEditor()
{
    if (!m_currentSelectedFlange) return;
    double minD = m_result.inlet_D * 1000.0;

    FlangeConfigDialog dlg(
        *m_currentSelectedFlange,
        m_result.nozzle_shell_thickness,
        m_result.nozzle_shell_length,
        m_standardFlanges,
        minD,
        this);

    if (dlg.exec() == QDialog::Accepted) {
        m_currentSelectedFlange = dlg.getSelectedFlange();
        m_result.nozzle_shell_thickness = dlg.getShellThickness();
        m_result.nozzle_shell_length = dlg.getShellLength();
        m_flangeLabel->setText(getFlangeSummary());
    }
}

void ResultDialog::autoSelectShellFlange()
{
    double D_outer_mm = m_result.D * 1000.0
        + 2.0 * m_result.geometry.shell_thickness * 1000.0;

    for (const auto& f : m_standardFlanges) {
        if (f.inner_d >= D_outer_mm) {
            m_currentShellFlange = f;
            return;
        }
    }
    if (!m_standardFlanges.empty())
        m_currentShellFlange = m_standardFlanges.back();
}

QString ResultDialog::getShellFlangeSummary() const
{
    if (!m_currentShellFlange) return "Не задан";
    const auto& f = *m_currentShellFlange;
    return QString("%1  D1=%2 мм, D=%3 мм, n=%4")
        .arg(QString::fromStdString(f.name))
        .arg(f.inner_d, 0, 'f', 1)
        .arg(f.outer_d, 0, 'f', 1)
        .arg(f.bolt_count);
}

void ResultDialog::openShellFlangeEditor()
{
    if (!m_currentShellFlange) return;

    double D_outer_mm = m_result.D * 1000.0
        + 2.0 * m_result.geometry.shell_thickness * 1000.0;

    ShellFlangeConfigDialog dlg(
        *m_currentShellFlange,
        m_standardFlanges,
        D_outer_mm,
        this);

    if (dlg.exec() == QDialog::Accepted) {
        m_currentShellFlange = dlg.getResult();
        m_shellFlangeLabel->setText(getShellFlangeSummary());
    }
}


QStringList ResultDialog::buildWarnings() const
{
    QStringList warnings;
    const auto& r = m_result;

    const double d_inner_mm = r.geometry.d_inner * 1000.0;
    const double inlet_D_mm = r.inlet_D * 1000.0;
    const double channel_w_mm = r.channel_width * 1000.0;
    const double turns = r.turns;
    const double Re_hot = r.Re_hot;
    const double Re_cold = r.Re_cold;
    const double shell_thk_mm = r.geometry.shell_thickness * 1000.0;
    const double D_outer_mm = r.D * 1000.0;

    if (d_inner_mm < inlet_D_mm * 2.0)
        warnings << QString(
            "Внутренний диаметр спирали (%1 мм) меньше удвоенного расчётного "
            "диаметра входного отверстия (%2 мм × 2 = %3 мм). "
            "Рекомендуется увеличить внутренний диаметр спирали.")
        .arg(d_inner_mm, 0, 'f', 1)
        .arg(inlet_D_mm, 0, 'f', 1)
        .arg(inlet_D_mm * 2.0, 0, 'f', 1);

    if (channel_w_mm < inlet_D_mm)
        warnings << QString(
            "Ширина теплообменника (%1 мм) меньше расчётного диаметра "
            "входного отверстия (%2 мм). Патрубок не вписывается в торец.")
        .arg(channel_w_mm, 0, 'f', 1)
        .arg(inlet_D_mm, 0, 'f', 1);

    if (Re_hot > 0 && Re_hot < 10000)
        warnings << QString(
            "Число Re горячей среды (%1) ниже 10 000 — "
            "расчёт коэффициента теплоотдачи по формуле Дитуса–Белтера недостоверен.")
        .arg((int)Re_hot);

    if (Re_cold > 0 && Re_cold < 10000)
        warnings << QString(
            "Число Re холодной среды (%1) ниже 10 000 — "
            "расчёт коэффициента теплоотдачи по формуле Дитуса–Белтера недостоверен.")
        .arg((int)Re_cold);

    if (turns > 0 && turns < 2)
        warnings << QString(
            "Количество витков спирали (%1) меньше 2 — "
            "конструкция теплообменника нецелесообразна.")
        .arg((int)turns);

    if (D_outer_mm > 4000.0)
        warnings << QString(
            "Наружный диаметр теплообменника (%1 мм) превышает 4 000 мм — "
            "проверьте исходные данные или разбейте на несколько аппаратов.")
        .arg(D_outer_mm, 0, 'f', 0);

    if (m_currentShellFlange) {
        double D_shell_outer_mm = D_outer_mm + 2.0 * shell_thk_mm;
        if (m_currentShellFlange->inner_d < D_shell_outer_mm)
            warnings << QString(
                "Внутренний диаметр фланца обечайки (%1 мм) меньше "
                "наружного диаметра корпуса (%2 мм).")
            .arg(m_currentShellFlange->inner_d, 0, 'f', 1)
            .arg(D_shell_outer_mm, 0, 'f', 1);
    }

    if (m_currentSelectedFlange) {
        if (m_currentSelectedFlange->inner_d < inlet_D_mm)
            warnings << QString(
                "Внутренний диаметр фланца патрубка (%1 мм) меньше "
                "расчётного диаметра входного отверстия (%2 мм).")
            .arg(m_currentSelectedFlange->inner_d, 0, 'f', 1)
            .arg(inlet_D_mm, 0, 'f', 1);
    }

    return warnings;
}

void ResultDialog::initStandardFlanges()
{
    m_standardFlanges = {
        { "DN10 PN1",    15.0,  75.0,  50.0, 10.0, 10.0, 4 },
        { "DN10 PN2.5",  15.0,  75.0,  50.0, 12.0, 10.0, 4 },
        { "DN10 PN6",    15.0,  75.0,  50.0, 12.0, 10.0, 4 },
        { "DN10 PN10",   18.0,  90.0,  60.0, 14.0, 12.0, 4 },
        { "DN10 PN16",   18.0,  90.0,  60.0, 14.0, 12.0, 4 },
        { "DN10 PN25",   18.0,  90.0,  60.0, 16.0, 12.0, 4 },

        { "DN15 PN1",    19.0,  80.0,  55.0, 10.0, 10.0, 4 },
        { "DN15 PN2.5",  19.0,  80.0,  55.0, 12.0, 10.0, 4 },
        { "DN15 PN6",    19.0,  80.0,  55.0, 12.0, 10.0, 4 },
        { "DN15 PN10",   22.0,  95.0,  65.0, 14.0, 12.0, 4 },
        { "DN15 PN16",   22.0,  95.0,  65.0, 14.0, 12.0, 4 },
        { "DN15 PN25",   22.0,  95.0,  65.0, 16.0, 12.0, 4 },

        { "DN20 PN1",    26.0,  90.0,  65.0, 12.0, 10.0, 4 },
        { "DN20 PN2.5",  26.0,  90.0,  65.0, 14.0, 10.0, 4 },
        { "DN20 PN6",    26.0,  90.0,  65.0, 14.0, 10.0, 4 },
        { "DN20 PN10",   27.5, 105.0,  75.0, 16.0, 12.0, 4 },
        { "DN20 PN16",   27.5, 105.0,  75.0, 16.0, 12.0, 4 },
        { "DN20 PN25",   27.5, 105.0,  75.0, 18.0, 12.0, 4 },

        { "DN25 PN1",    33.0, 100.0,  75.0, 12.0, 10.0, 4 },
        { "DN25 PN2.5",  33.0, 100.0,  75.0, 14.0, 10.0, 4 },
        { "DN25 PN6",    33.0, 100.0,  75.0, 14.0, 10.0, 4 },
        { "DN25 PN10",   34.5, 115.0,  85.0, 16.0, 12.0, 4 },
        { "DN25 PN16",   34.5, 115.0,  85.0, 16.0, 12.0, 4 },
        { "DN25 PN25",   34.5, 115.0,  85.0, 18.0, 12.0, 4 },

        { "DN32 PN1",    39.0, 120.0,  90.0, 12.0, 12.0, 4 },
        { "DN32 PN2.5",  39.0, 120.0,  90.0, 16.0, 12.0, 4 },
        { "DN32 PN6",    39.0, 120.0,  90.0, 15.0, 12.0, 4 },
        { "DN32 PN10",   43.5, 135.0, 100.0, 16.0, 16.0, 4 },
        { "DN32 PN16",   43.5, 140.0, 100.0, 18.0, 16.0, 4 },
        { "DN32 PN25",   43.5, 140.0, 100.0, 20.0, 16.0, 4 },

        { "DN40 PN1",    46.0, 130.0, 100.0, 13.0, 12.0, 4 },
        { "DN40 PN2.5",  46.0, 130.0, 100.0, 16.0, 12.0, 4 },
        { "DN40 PN6",    46.0, 130.0, 100.0, 16.0, 12.0, 4 },
        { "DN40 PN10",   49.5, 145.0, 110.0, 18.0, 16.0, 4 },
        { "DN40 PN16",   49.5, 150.0, 110.0, 18.0, 16.0, 4 },
        { "DN40 PN25",   49.5, 150.0, 110.0, 22.0, 16.0, 4 },

        { "DN50 PN1",    59.0, 140.0, 110.0, 13.0, 12.0, 4 },
        { "DN50 PN2.5",  59.0, 140.0, 110.0, 16.0, 12.0, 4 },
        { "DN50 PN6",    59.0, 140.0, 110.0, 16.0, 12.0, 4 },
        { "DN50 PN10",   61.5, 160.0, 125.0, 18.0, 16.0, 4 },
        { "DN50 PN16",   61.5, 165.0, 125.0, 20.0, 16.0, 4 },
        { "DN50 PN25",   61.5, 165.0, 125.0, 24.0, 16.0, 4 },

        { "DN65 PN1",    78.0, 160.0, 130.0, 14.0, 12.0, 4 },
        { "DN65 PN2.5",  78.0, 160.0, 130.0, 16.0, 12.0, 4 },
        { "DN65 PN6",    78.0, 160.0, 130.0, 16.0, 12.0, 4 },
        { "DN65 PN10",   77.5, 180.0, 145.0, 20.0, 16.0, 4 },
        { "DN65 PN16",   77.5, 185.0, 145.0, 20.0, 16.0, 8 },
        { "DN65 PN25",   77.5, 185.0, 145.0, 22.0, 16.0, 8 },

        { "DN80 PN1",    91.0, 185.0, 150.0, 14.0, 18.0, 4 },
        { "DN80 PN2.5",  91.0, 185.0, 150.0, 14.0, 18.0, 4 },
        { "DN80 PN6",    91.0, 185.0, 150.0, 18.0, 18.0, 4 },
        { "DN80 PN10",   90.5, 190.0, 150.0, 20.0, 18.0, 4 },
        { "DN80 PN16",   90.5, 195.0, 160.0, 24.0, 18.0, 8 },
        { "DN80 PN25",   90.5, 200.0, 160.0, 24.0, 18.0, 8 },

        { "DN100 PN1",   110.0, 205.0, 170.0, 14.0, 18.0,  4 },
        { "DN100 PN2.5", 110.0, 205.0, 170.0, 18.0, 18.0,  4 },
        { "DN100 PN6",   100.0, 205.0, 170.0, 18.0, 18.0,  4 },
        { "DN100 PN10",  116.0, 210.0, 180.0, 22.0, 18.0,  8 },
        { "DN100 PN16",  116.0, 220.0, 180.0, 22.0, 18.0,  8 },
        { "DN100 PN25",  116.0, 235.0, 190.0, 26.0, 22.0,  8 },

        { "DN125 PN1",   135.0, 235.0, 200.0, 16.0, 18.0,  8 },
        { "DN125 PN2.5", 135.0, 235.0, 200.0, 16.0, 18.0,  8 },
        { "DN125 PN6",   135.0, 240.0, 200.0, 20.0, 18.0,  8 },
        { "DN125 PN10",  141.5, 245.0, 210.0, 24.0, 18.0,  8 },
        { "DN125 PN16",  141.5, 250.0, 210.0, 28.0, 18.0,  8 },
        { "DN125 PN25",  141.5, 270.0, 220.0, 22.0, 26.0,  8 },

        { "DN150 PN1",   154.0, 260.0, 225.0, 16.0, 18.0,  8 },
        { "DN150 PN2.5", 154.0, 260.0, 225.0, 16.0, 18.0,  8 },
        { "DN150 PN6",   154.0, 265.0, 225.0, 20.0, 18.0,  8 },
        { "DN150 PN10",  170.5, 280.0, 240.0, 24.0, 22.0,  8 },
        { "DN150 PN16",  170.5, 285.0, 240.0, 24.0, 22.0,  8 },
        { "DN150 PN25",  170.5, 300.0, 250.0, 30.0, 26.0,  8 },

        { "DN200 PN1",   222.0, 315.0, 280.0, 18.0, 18.0,  8 },
        { "DN200 PN2.5", 222.0, 315.0, 280.0, 22.0, 18.0,  8 },
        { "DN200 PN6",   222.0, 320.0, 280.0, 22.0, 18.0,  8 },
        { "DN200 PN10",  221.5, 335.0, 295.0, 24.0, 22.0,  8 },
        { "DN200 PN16",  221.5, 340.0, 295.0, 26.0, 22.0,  8 },
        { "DN200 PN25",  221.5, 360.0, 310.0, 32.0, 26.0, 12 },

        { "DN400 PN1",   426.0,  535.0,  495.0, 22.0, 22.0, 16 },
        { "DN400 PN2.5", 426.0,  540.0,  495.0, 28.0, 22.0, 16 },
        { "DN400 PN6",   426.0,  540.0,  495.0, 28.0, 22.0, 16 },
        { "DN400 PN10",  411.0,  565.0,  515.0, 32.0, 26.0, 16 },
        { "DN400 PN16",  411.0,  580.0,  525.0, 38.0, 30.0, 16 },
        { "DN400 PN25",  411.0,  620.0,  550.0, 48.0, 36.0, 16 },

        { "DN800 PN1",   820.0,  975.0,  920.0, 26.0, 30.0, 24 },
        { "DN800 PN2.5", 820.0,  975.0,  920.0, 44.0, 30.0, 24 },
        { "DN800 PN6",   820.0,  975.0,  920.0, 44.0, 30.0, 24 },
        { "DN800 PN10",  820.0, 1015.0,  950.0, 56.0, 33.0, 24 },
        { "DN800 PN16",  820.0, 1025.0,  950.0, 74.0, 39.0, 24 },
        { "DN800 PN25",  820.0, 1085.0,  990.0, 95.0, 48.0, 24 },

        { "DN900 PN1",   920.0, 1075.0, 1020.0, 28.0, 30.0, 24 },
        { "DN900 PN2.5", 920.0, 1075.0, 1020.0, 48.0, 30.0, 24 },
        { "DN900 PN6",   920.0, 1075.0, 1020.0, 48.0, 30.0, 24 },
        { "DN900 PN10",  920.0, 1115.0, 1050.0, 62.0, 33.0, 28 },
        { "DN900 PN16",  920.0, 1125.0, 1050.0, 82.0, 39.0, 28 },

        { "DN1000 PN1",   1020.0, 1175.0, 1120.0, 30.0, 30.0, 28 },
        { "DN1000 PN2.5", 1020.0, 1175.0, 1120.0, 52.0, 30.0, 28 },
        { "DN1000 PN6",   1020.0, 1175.0, 1120.0, 52.0, 30.0, 28 },
        { "DN1000 PN10",  1020.0, 1230.0, 1160.0, 70.0, 36.0, 28 },
        { "DN1000 PN16",  1020.0, 1255.0, 1170.0, 90.0, 42.0, 28 },

        { "DN1200 PN1",   1220.0, 1375.0, 1320.0, 30.0, 30.0, 32 },
        { "DN1200 PN2.5", 1220.0, 1375.0, 1320.0, 60.0, 30.0, 32 },
        { "DN1200 PN6",   1220.0, 1405.0, 1340.0, 60.0, 33.0, 32 },
        { "DN1200 PN10",  1220.0, 1455.0, 1380.0, 83.0, 39.0, 32 },
        { "DN1200 PN16",  1220.0, 1485.0, 1390.0, 76.0, 48.0, 32 },

        { "DN1400 PN1",   1420.0, 1575.0, 1520.0, 32.0, 30.0, 36 },
        { "DN1400 PN2.5", 1420.0, 1630.0, 1560.0, 72.0, 36.0, 36 },
        { "DN1400 PN10",  1420.0, 1675.0, 1590.0, 65.0, 42.0, 36 },

        { "DN1600 PN1",   1620.0, 1785.0, 1730.0, 32.0, 30.0, 40 },
        { "DN1600 PN2.5", 1620.0, 1785.0, 1730.0, 32.0, 30.0, 40 },
        { "DN1600 PN6",   1620.0, 1830.0, 1760.0, 80.0, 36.0, 40 },
        { "DN1600 PN10",  1620.0, 1915.0, 1820.0, 75.0, 48.0, 40 },

        { "DN1800 PN1",   1820.0, 1985.0, 1930.0, 35.0, 30.0, 44 },
        { "DN1800 PN2.5", 1820.0, 1985.0, 1930.0, 35.0, 30.0, 44 },
        { "DN1800 PN6",   1820.0, 2045.0, 1970.0, 88.0, 39.0, 44 },

        { "DN2000 PN1",   2020.0, 2190.0, 2130.0, 35.0, 30.0, 48 },
        { "DN2000 PN2.5", 2020.0, 2190.0, 2130.0, 35.0, 30.0, 48 },
        { "DN2000 PN6",   2020.0, 2265.0, 2180.0, 96.0, 42.0, 48 },

        { "DN2200 PN1",   2220.0, 2405.0, 2340.0, 42.0, 33.0, 52 },
        { "DN2200 PN2.5", 2220.0, 2405.0, 2340.0, 42.0, 33.0, 52 },

        { "DN2400 PN1",   2420.0, 2605.0, 2540.0, 47.0, 33.0, 56 },
    };
}

void ResultDialog::onSaveCalc()
{
    CalculationResult snapshot = m_result;
    if (m_currentSelectedFlange)
        snapshot.selected_flange = *m_currentSelectedFlange;
    if (m_currentShellFlange)
        snapshot.shell_flange = *m_currentShellFlange;
    if (m_gasketThicknessSpin)
        snapshot.gasket_thickness = m_gasketThicknessSpin->value() / 1000.0;
    if (m_coverThicknessSpin)
        snapshot.geometry.cover_thickness = m_coverThicknessSpin->value() / 1000.0;
    if (m_shellThicknessSpin)
        snapshot.geometry.shell_thickness = m_shellThicknessSpin->value() / 1000.0;

    QString selectedFilter;
    QString path = QFileDialog::getSaveFileName(
        this, "Сохранить расчёт", {},
        "Файл расчёта SpiralHX (*.txt);;"
        "PDF документ (*.pdf)",
        &selectedFilter);
    if (path.isEmpty()) return;

    QString err;
    if (selectedFilter.contains("*.pdf")) {
        if (!path.endsWith(".pdf", Qt::CaseInsensitive)) path += ".pdf";
        err = CalcResultSerializer::savePdf(snapshot, path);
    }
    else {
        if (!path.endsWith(".txt", Qt::CaseInsensitive)) path += ".txt";
        err = CalcResultSerializer::save(snapshot, path);
    }

    if (err.isEmpty())
        QMessageBox::information(this, "Сохранение", "Файл сохранён:\n" + path);
    else
        QMessageBox::critical(this, "Ошибка", err);
}