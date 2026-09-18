#pragma once
#include <QDialog>
#include <QDoubleSpinBox>
#include <vector>
#include <optional>
#include "SpiralHeatExchanger.h"

class QFormLayout;
class QLabel;
class QPushButton;

class ResultDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ResultDialog(const CalculationResult& res, QWidget* parent = nullptr);

signals:
    void selectedResultConfirmed(const CalculationResult& r);

private slots:
    void openFlangeEditor();
    void openShellFlangeEditor();
    void onSaveCalc();

private:
    void addRow(QFormLayout* layout, const QString& label,
        const QString& value, bool isHeader = false);

    void addRowHotCold(QFormLayout* layout, const QString& label,
        const QString& hotValue, const QString& coldValue,
        const QString& suffix = {});

    void    initStandardFlanges();
    void    autoSelectFlange();
    QString getFlangeSummary() const;

    void    autoSelectShellFlange();
    QString getShellFlangeSummary() const;

    CalculationResult     m_result;
    std::vector<Flange>   m_standardFlanges;

    std::optional<Flange> m_currentSelectedFlange;
    std::optional<Flange> m_currentShellFlange;

    QLabel* m_flangeLabel = nullptr;
    QLabel* m_shellFlangeLabel = nullptr;
    QPushButton* m_confirmBtn = nullptr;
    QPushButton* m_saveCalcBtn = nullptr;
    QDoubleSpinBox* m_gasketThicknessSpin = nullptr;
    QDoubleSpinBox* m_shellThicknessSpin = nullptr;
    QDoubleSpinBox* m_coverThicknessSpin = nullptr;

    QStringList buildWarnings() const;
};