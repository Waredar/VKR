#include "FlangeConfigDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QPixmap>
#include <QGroupBox>
#include <set>
#include <cmath>

FlangeConfigDialog::FlangeConfigDialog(const Flange& current,
    double shellThicknessMm,
    double shellLengthMm,
    const std::vector<Flange>& all,
    double minInnerD,
    QWidget* parent)
    : QDialog(parent)
    , m_all(all)
    , m_current(current)
    , m_minInnerD(minInnerD)
    , m_shellThickness(shellThicknessMm)
    , m_shellLength(shellLengthMm)
{
    setWindowTitle("Настройка параметров фланца патрубка");
    setupUi();
    initCombos();
}

void FlangeConfigDialog::setupUi()
{
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    // Схема
    m_imageLabel = new QLabel();
    m_imageLabel->setFixedSize(300, 300);
    m_imageLabel->setAlignment(Qt::AlignCenter);
    m_imageLabel->setStyleSheet(
        "border: 1px solid #bdc3c7; background: white; border-radius: 4px;");
    QPixmap pix(":/images/flange_drawing.png");
    if (!pix.isNull())
        m_imageLabel->setPixmap(
            pix.scaled(280, 280, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    else
        m_imageLabel->setText("Схема фланца");
    mainLayout->addWidget(m_imageLabel);

    auto* rightLayout = new QVBoxLayout();

    // Чекбокс режима
    m_standardCheck = new QCheckBox("Стандартные значения");
    m_standardCheck->setChecked(true);
    rightLayout->addWidget(m_standardCheck);

    // ── Стек: страница 0 — комбобоксы, страница 1 — ручной ввод ──────────
    m_stack = new QStackedWidget();

    // Страница 0: стандартные комбобоксы
    auto* pageCombo = new QWidget();
    auto* formCombo = new QFormLayout(pageCombo);
    const QString labels[7] = {
        "Наименование:",
        "Внутренний диаметр (D1), мм:",
        "Наружный диаметр (D), мм:",
        "Болтовой круг (D2), мм:",
        "Толщина тарелки (b), мм:",
        "Диаметр отверстий (d), мм:",
        "Кол-во болтов (n), шт:"
    };
    for (int i = 0; i < 7; ++i) {
        m_combos[i] = new QComboBox();
        formCombo->addRow(labels[i], m_combos[i]);
        if (i == 1)
            connect(m_combos[i], QOverload<int>::of(&QComboBox::currentIndexChanged),
                [this](int) { updateCascade(1); });
    }
    m_stack->addWidget(pageCombo);   // index 0

    // Страница 1: ручной ввод
    auto* pageManual = new QWidget();
    auto* formManual = new QFormLayout(pageManual);

    auto makeDSpin = [](double min, double max, int dec = 1) {
        auto* s = new QDoubleSpinBox();
        s->setRange(min, max);
        s->setDecimals(dec);
        s->setButtonSymbols(QAbstractSpinBox::NoButtons);
        s->setSuffix(" мм");
        return s;
        };

    m_mInnerD = makeDSpin(1, 5000);
    m_mOuterD = makeDSpin(1, 5000);
    m_mBoltCircD = makeDSpin(1, 5000);
    m_mFlangThk = makeDSpin(1, 500);
    m_mBoltD = makeDSpin(1, 200);
    m_mBoltN = new QSpinBox();
    m_mBoltN->setRange(1, 200);
    m_mBoltN->setButtonSymbols(QAbstractSpinBox::NoButtons);

    // Заполнить ручные поля текущими значениями
    m_mInnerD->setValue(m_current.inner_d);
    m_mOuterD->setValue(m_current.outer_d);
    m_mBoltCircD->setValue(m_current.bolt_circle_d);
    m_mFlangThk->setValue(m_current.flange_thickness);
    m_mBoltD->setValue(m_current.bolt_d);
    m_mBoltN->setValue(m_current.bolt_count);

    formManual->addRow("Внутренний диаметр (D1), мм:", m_mInnerD);
    formManual->addRow("Наружный диаметр (D), мм:", m_mOuterD);
    formManual->addRow("Болтовой круг (D2), мм:", m_mBoltCircD);
    formManual->addRow("Толщина тарелки (b), мм:", m_mFlangThk);
    formManual->addRow("Диаметр отверстий (d), мм:", m_mBoltD);
    formManual->addRow("Кол-во болтов (n), шт:", m_mBoltN);
    m_stack->addWidget(pageManual);  // index 1

    rightLayout->addWidget(m_stack);

    // Общие поля патрубка (всегда видны)
    auto* formCommon = new QFormLayout();

    m_shellThicknessEdit = new QDoubleSpinBox();
    m_shellThicknessEdit->setRange(0.5, 100.0);
    m_shellThicknessEdit->setDecimals(1);
    m_shellThicknessEdit->setSuffix(" мм");
    m_shellThicknessEdit->setValue(m_shellThickness);
    m_shellThicknessEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    formCommon->addRow("Толщина обечайки (s), мм:", m_shellThicknessEdit);

    m_shellLengthEdit = new QDoubleSpinBox();
    m_shellLengthEdit->setRange(0.1, 10000.0);
    m_shellLengthEdit->setDecimals(1);
    m_shellLengthEdit->setSuffix(" мм");
    m_shellLengthEdit->setValue(m_shellLength);
    m_shellLengthEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    formCommon->addRow("Длина патрубка (L), мм:", m_shellLengthEdit);

    rightLayout->addLayout(formCommon);
    rightLayout->addStretch();

    // Кнопки
    auto* buttons = new QHBoxLayout();
    auto* okBtn = new QPushButton("Принять");
    auto* cancelBtn = new QPushButton("Отмена");
    connect(okBtn, &QPushButton::clicked, this, &FlangeConfigDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    buttons->addStretch();
    buttons->addWidget(cancelBtn);
    buttons->addWidget(okBtn);
    rightLayout->addLayout(buttons);

    mainLayout->addLayout(rightLayout);
    okBtn->setFocus();

    connect(m_standardCheck, &QCheckBox::toggled,
        this, &FlangeConfigDialog::onStandardToggled);
}

void FlangeConfigDialog::onStandardToggled(bool checked)
{
    m_stack->setCurrentIndex(checked ? 0 : 1);

    // При переключении в ручной режим — синхронизировать поля
    // из текущего выбранного стандартного фланца
    if (!checked && m_combos[1]->currentData().isValid()) {
        double d1 = m_combos[1]->currentData().toDouble();
        for (const auto& f : m_all) {
            if (std::abs(f.inner_d - d1) < 0.001) {
                m_mInnerD->setValue(f.inner_d);
                m_mOuterD->setValue(f.outer_d);
                m_mBoltCircD->setValue(f.bolt_circle_d);
                m_mFlangThk->setValue(f.flange_thickness);
                m_mBoltD->setValue(f.bolt_d);
                m_mBoltN->setValue(f.bolt_count);
                break;
            }
        }
    }
}

void FlangeConfigDialog::initCombos()
{
    for (int i = 0; i < 7; ++i) m_combos[i]->blockSignals(true);

    std::set<double> innerDiameters;
    for (const auto& f : m_all)
        if (f.inner_d >= m_minInnerD)
            innerDiameters.insert(f.inner_d);

    if (innerDiameters.empty() && !m_all.empty()) {
        double best = m_all[0].inner_d;
        for (const auto& f : m_all) if (f.inner_d > best) best = f.inner_d;
        innerDiameters.insert(best);
    }

    for (double d : innerDiameters)
        m_combos[1]->addItem(QString::number(d), d);

    int dIdx = m_combos[1]->findData(m_current.inner_d);
    m_combos[1]->setCurrentIndex(dIdx >= 0 ? dIdx : 0);

    for (int i = 0; i < 7; ++i) m_combos[i]->blockSignals(false);
    updateCascade(1);
}

void FlangeConfigDialog::updateCascade(int level)
{
    if (level != 1) return;

    double selectedD1 = m_combos[1]->currentData().toDouble();

    for (int i = 0; i < 7; ++i) if (i != 1) m_combos[i]->blockSignals(true);
    for (int i = 0; i < 7; ++i) if (i != 1) m_combos[i]->clear();

    std::set<std::string> names;
    std::set<double>      d_out, bolt_c, thick, b_diam, b_count;

    for (const auto& f : m_all) {
        if (std::abs(f.inner_d - selectedD1) < 0.001) {
            names.insert(f.name);
            d_out.insert(f.outer_d);
            bolt_c.insert(f.bolt_circle_d);
            thick.insert(f.flange_thickness);
            b_diam.insert(f.bolt_d);
            b_count.insert(static_cast<double>(f.bolt_count));
        }
    }

    auto fillStr = [&](int idx, const std::set<std::string>& vals) {
        for (const auto& v : vals) m_combos[idx]->addItem(QString::fromStdString(v));
        };
    auto fillNum = [&](int idx, const std::set<double>& vals) {
        for (double v : vals) m_combos[idx]->addItem(QString::number(v), v);
        };

    fillStr(0, names);
    fillNum(2, d_out);
    fillNum(3, bolt_c);
    fillNum(4, thick);
    fillNum(5, b_diam);
    fillNum(6, b_count);

    for (int i = 0; i < 7; ++i) m_combos[i]->blockSignals(false);
}

Flange FlangeConfigDialog::flangeFromManual() const
{
    Flange f;
    f.inner_d = m_mInnerD->value();
    f.outer_d = m_mOuterD->value();
    f.bolt_circle_d = m_mBoltCircD->value();
    f.flange_thickness = m_mFlangThk->value();
    f.bolt_d = m_mBoltD->value();
    f.bolt_count = m_mBoltN->value();
    f.name = "(пользоват.)";
    return f;
}

void FlangeConfigDialog::onAccept()
{
    if (m_standardCheck->isChecked()) {
        m_current.name = m_combos[0]->currentText().toStdString();
        m_current.inner_d = m_combos[1]->currentData().toDouble();
        m_current.outer_d = m_combos[2]->currentData().toDouble();
        m_current.bolt_circle_d = m_combos[3]->currentData().toDouble();
        m_current.flange_thickness = m_combos[4]->currentData().toDouble();
        m_current.bolt_d = m_combos[5]->currentData().toDouble();
        m_current.bolt_count = m_combos[6]->currentData().toInt();
    }
    else {
        m_current = flangeFromManual();
    }

    m_shellThickness = m_shellThicknessEdit->value();
    m_shellLength = m_shellLengthEdit->value();

    accept();
}