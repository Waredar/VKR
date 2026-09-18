#pragma once
#include <QDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QStackedWidget>
#include <vector>
#include "SpiralHeatExchanger.h"

class ShellFlangeConfigDialog : public QDialog
{
    Q_OBJECT
public:
    ShellFlangeConfigDialog(const Flange& current,
        const std::vector<Flange>& all,
        double minInnerD,
        QWidget* parent = nullptr);

    Flange getResult() const { return m_current; }

private slots:
    void updateCascade(int level);
    void onAccept();
    void onStandardToggled(bool checked);

private:
    void setupUi();
    void initCombos();
    Flange flangeFromManual() const;

    const std::vector<Flange> m_all;
    Flange  m_current;
    double  m_minInnerD;

    QLabel* m_imageLabel = nullptr;
    QCheckBox* m_standardCheck = nullptr;
    QStackedWidget* m_stack = nullptr;  

    QComboBox* m_combos[7];

    QDoubleSpinBox* m_mInnerD = nullptr;
    QDoubleSpinBox* m_mOuterD = nullptr;
    QDoubleSpinBox* m_mBoltCircD = nullptr;
    QDoubleSpinBox* m_mFlangThk = nullptr;
    QDoubleSpinBox* m_mBoltD = nullptr;
    QSpinBox* m_mBoltN = nullptr;
};