#include "ShellFlangeConfigDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QPixmap>
#include <set>
#include <cmath>

ShellFlangeConfigDialog::ShellFlangeConfigDialog(
    const Flange& current,
    const std::vector<Flange>& all,
    double minInnerD,
    QWidget* parent)
    : QDialog(parent)
    , m_all(all)
    , m_current(current)
    , m_minInnerD(minInnerD)
{
    setWindowTitle("Настройка параметров фланца обечайки");
    setupUi();
    initCombos();
}

void ShellFlangeConfigDialog::setupUi()
{
    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

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

    auto* infoLabel = new QLabel(
        QString("Наружный диаметр обечайки: <b>%1 мм</b>")
        .arg(m_minInnerD, 0, 'f', 1));
    infoLabel->setStyleSheet("color: #888; font-size: 9pt; margin-bottom: 6px;");
    rightLayout->addWidget(infoLabel);

    m_standardCheck = new QCheckBox("Стандартные значения");
    m_standardCheck->setChecked(true);
    rightLayout->addWidget(m_standardCheck);

    m_stack = new QStackedWidget();

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
    m_stack->addWidget(pageCombo); 

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
    m_stack->addWidget(pageManual);  

    rightLayout->addWidget(m_stack);
    rightLayout->addStretch();

    auto* buttons = new QHBoxLayout();
    auto* okBtn = new QPushButton("Принять");
    auto* cancelBtn = new QPushButton("Отмена");
    connect(okBtn, &QPushButton::clicked, this, &ShellFlangeConfigDialog::onAccept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    buttons->addStretch();
    buttons->addWidget(cancelBtn);
    buttons->addWidget(okBtn);
    rightLayout->addLayout(buttons);

    mainLayout->addLayout(rightLayout);
    okBtn->setFocus();

    connect(m_standardCheck, &QCheckBox::toggled,
        this, &ShellFlangeConfigDialog::onStandardToggled);
}

void ShellFlangeConfigDialog::onStandardToggled(bool checked)
{
    m_stack->setCurrentIndex(checked ? 0 : 1);

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

void ShellFlangeConfigDialog::initCombos()
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

void ShellFlangeConfigDialog::updateCascade(int level)
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

Flange ShellFlangeConfigDialog::flangeFromManual() const
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

void ShellFlangeConfigDialog::onAccept()
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
    accept();
}