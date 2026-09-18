#pragma once

#include <QWidget>
#include <QCheckBox>
#include <QThread>
#include <QProgressDialog>
#include "SpiralHeatExchanger.h"
#include "ModelBuilder.h"
#include "solid.h"
#include "assembly.h"

class QTabWidget;
class QPushButton;
class QDoubleSpinBox;
class QComboBox;
class QFormLayout;
class QGroupBox;
class CleanDoubleSpinBox;
class CalcSceneWidget;

class ModelBuildWorker : public QObject
{
    Q_OBJECT
public:
    explicit ModelBuildWorker(const CalculationResult& result, QObject* parent = nullptr)
        : QObject(parent), m_result(result) {
    }

signals:
    void progress(int step, int total, const QString& description);
    void finished(SPtr<MbAssembly> assembly);

public slots:
    void run() {
        ModelBuilder builder;
        builder.setProgressCallback([this](int step, int total, const QString& desc) {
            emit progress(step, total, desc);
            });
        auto assembly = builder.BuildModel(m_result);
        emit finished(assembly);
    }

private:
    CalculationResult m_result;
};

struct FlangeRecord {
    double d_outer;
    double d_inner;
    double bcd;
    double plate_thk;
    double bolt_d;
    int    bolt_n;
    double shell_thk;
    double shell_len;
};

class CalcManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalcManagerWidget(QWidget* parent = nullptr);
    void setViewport(CalcSceneWidget* vp) { m_viewport = vp; }
    void buildModelFromResult(const CalculationResult& result);

private slots:
    void onCalculate();

private:
    struct FluidUI {
        CleanDoubleSpinBox* G;
        CleanDoubleSpinBox* t_in;
        CleanDoubleSpinBox* t_out;
        CleanDoubleSpinBox* rho;
        CleanDoubleSpinBox* cp;
        CleanDoubleSpinBox* lambda;
        CleanDoubleSpinBox* viscosity;
        CleanDoubleSpinBox* max_velocity;
        CleanDoubleSpinBox* t_avg;
    };

    struct WallUI {
        CleanDoubleSpinBox* lambda;
        CleanDoubleSpinBox* fouling;
    };

    struct GeometryUI {
        CleanDoubleSpinBox* width_hot;
        CleanDoubleSpinBox* width_cold;
        CleanDoubleSpinBox* d_inner;
        CleanDoubleSpinBox* thickness_mm;

        QCheckBox* autoWidthCheck;
        CleanDoubleSpinBox* widthMin;
        CleanDoubleSpinBox* widthMax;
    };

    struct FlangeUI {
        QComboBox* d_outer;
        QComboBox* d_inner;
        QComboBox* bcd;
        QComboBox* plate_thk;
        QComboBox* bolt_d;
        QComboBox* bolt_n;
        QComboBox* shell_thk;
        QComboBox* shell_len;
    };

    QTabWidget* tabs;
    QPushButton* calcButton;

    QList<FlangeRecord> flanges;

    FluidUI hot;
    FluidUI cold;
    WallUI wall;
    GeometryUI geom;
    FlangeUI flange;
    CalcSceneWidget* m_viewport = nullptr;

private:
    QWidget* createFluidsTab();
    void setupAutoCalc();
    void onBalanceEdited();
    void solveBalance();
    void updateAverageTemps();
    QWidget* createGeometryTab();
    void addRowWithUnit(QFormLayout* form, const QString& name, QDoubleSpinBox* spin, const QString& unit);

    Fluid toFluid(const FluidUI& ui);
    Wall toWall(const WallUI& ui);
    Geometry toGeometry(const GeometryUI& ui);

    void buildModel(const CalculationResult& result);
    void setDefaults();
};