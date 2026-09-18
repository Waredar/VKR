#pragma once
#include <QDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QStackedWidget>
#include <vector>
#include <string>
#include "SpiralHeatExchanger.h"

class FlangeConfigDialog : public QDialog {
    Q_OBJECT
public:
    FlangeConfigDialog(const Flange& current,
        double shellThicknessMm,
        double shellLengthMm,
        const std::vector<Flange>& all,
        double minInnerD,
        QWidget* parent = nullptr);

    Flange getSelectedFlange()  const { return m_current; }
    double getShellThickness()  const { return m_shellThickness; }
    double getShellLength()     const { return m_shellLength; }

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
    double  m_shellThickness;
    double  m_shellLength;

    QLabel* m_imageLabel = nullptr;
    QCheckBox* m_standardCheck = nullptr;
    QStackedWidget* m_stack = nullptr;  

    QComboBox* m_combos[7];

    QDoubleSpinBox* m_mName = nullptr; 
    QDoubleSpinBox* m_mInnerD = nullptr;
    QDoubleSpinBox* m_mOuterD = nullptr;
    QDoubleSpinBox* m_mBoltCircD = nullptr;
    QDoubleSpinBox* m_mFlangThk = nullptr;
    QDoubleSpinBox* m_mBoltD = nullptr;
    QSpinBox* m_mBoltN = nullptr;

    QDoubleSpinBox* m_shellThicknessEdit = nullptr;
    QDoubleSpinBox* m_shellLengthEdit = nullptr;
};