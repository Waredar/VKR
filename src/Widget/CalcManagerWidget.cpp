#include "CalcManagerWidget.h"
#include "SpiralHeatExchanger.h"
#include "ResultDialog.h"
#include "ModelBuilder.h"
#include "CalcSceneWidget.h"

#include <QVBoxLayout>
#include <QTabWidget>
#include <QGroupBox>
#include <QFormLayout>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>
#include <QToolTip>
#include <QKeyEvent>
#include <QThread>
#include <QProgressDialog>


class CleanDoubleSpinBox : public QDoubleSpinBox
{
public:
    using QDoubleSpinBox::QDoubleSpinBox;

    void setRangeWithWarning(double min, double max, const QString& msg = "") {
        setRange(min, max);
        m_warningText = msg.isEmpty()
            ? QString("Значение должно быть в диапазоне от %1 до %2").arg(min).arg(max)
            : msg;
    }

protected:
    QString m_warningText;

    void validateValue() {
        if (value() >= maximum() || value() <= minimum()) {
            QToolTip::showText(mapToGlobal(QPoint(width() / 2, 0)), m_warningText, this);
            this->setStyleSheet("border: 1px solid #FF4444; background-color: #FFF0F0;");
            QTimer::singleShot(1500, this, [this]() { this->setStyleSheet(""); });
        }
    }

    QString textFromValue(double value) const override {
        if (!hasFocus() && value == 0.0)
            return "";
        QString s = QString::number(value, 'f', decimals());
        if (s.contains('.')) {
            while (s.endsWith('0')) s.chop(1);
            if (s.endsWith('.')) s.chop(1);
        }
        return s;
    }

    void focusInEvent(QFocusEvent* event) override {
        QDoubleSpinBox::focusInEvent(event);
        QTimer::singleShot(0, this, [this]() {
            if (lineEdit()) lineEdit()->selectAll();
            });
    }

    void focusOutEvent(QFocusEvent* event) override {
        validateValue();
        QDoubleSpinBox::focusOutEvent(event);
    }

    void keyPressEvent(QKeyEvent* event) override {
        QDoubleSpinBox::keyPressEvent(event);
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            validateValue();
        }
    }
};

CalcManagerWidget::CalcManagerWidget(QWidget* parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout(this);

    tabs = new QTabWidget(this);
    tabs->addTab(createFluidsTab(), "Теплоносители");
    tabs->addTab(createGeometryTab(), "Геометрия");

    layout->addWidget(tabs);

    calcButton = new QPushButton("Рассчитать", this);
    calcButton->setFixedHeight(40);
    calcButton->setStyleSheet("font-weight: bold;");
    layout->addWidget(calcButton);
    layout->addStretch();

    connect(calcButton, &QPushButton::clicked, this, &CalcManagerWidget::onCalculate);

    setDefaults();
}

QWidget* CalcManagerWidget::createFluidsTab()
{
    auto w = new QWidget;
    auto layout = new QVBoxLayout(w);

    auto makeFlowSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setDecimals(3);
        s->setButtonSymbols(QAbstractSpinBox::NoButtons);
        s->setRangeWithWarning(0.0, 1000.0, "Расход должен быть в пределах 0 - 1000 кг/с (0 для авторасчета)");
        return s;
        };

    auto makeTempSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setDecimals(2);
        s->setButtonSymbols(QAbstractSpinBox::NoButtons);
        s->setRangeWithWarning(-100.0, 600.0, "Температура вне промышленного диапазона (-100...600°C)");
        return s;
        };

    auto makeRhoSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setDecimals(2);
        s->setRangeWithWarning(0.5, 5000.0, "Плотность должна быть от 0.5 (газы) до 5000 (тяжелые среды) кг/м³");
        return s;
        };

    auto makeCpSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setDecimals(1);
        s->setRangeWithWarning(100.0, 10000.0, "Удельная теплоемкость обычно находится в пределах 100...10000 Дж/(кг·К)");
        return s;
        };

    auto makeLambdaSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setDecimals(4);
        s->setRangeWithWarning(0.01, 5.0, "Теплопроводность сред обычно варьируется от 0.01 до 5 Вт/(м·К)");
        return s;
        };

    auto makeViscSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setDecimals(4);
        s->setRangeWithWarning(0.001, 5000.0, "Динамическая вязкость должна быть в пределах 0.001 - 5000 мПа·с");
        return s;
        };

    auto makeVeloSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setDecimals(2);
        s->setRangeWithWarning(0.1, 15.0, "Скорость выше 10-15 м/с приводит к критическому износу стенок");
        return s;
        };

    auto balanceBox = new QGroupBox("Уравнение теплового баланса");
    auto grid = new QGridLayout(balanceBox);

    grid->addWidget(new QLabel("Параметр"), 0, 0);
    auto hLabel = new QLabel("Горячая среда");
    hLabel->setStyleSheet("font-weight: bold;");
    hLabel->setAlignment(Qt::AlignCenter);
    grid->addWidget(hLabel, 0, 1);

    auto cLabel = new QLabel("Холодная среда");
    cLabel->setStyleSheet("font-weight: bold;");
    cLabel->setAlignment(Qt::AlignCenter);
    grid->addWidget(cLabel, 0, 2);

    hot.G = makeFlowSB();
    hot.t_in = makeTempSB();
    hot.t_out = makeTempSB();

    cold.G = makeFlowSB();
    cold.t_in = makeTempSB();
    cold.t_out = makeTempSB();

    grid->addWidget(new QLabel("Расход, кг/с"), 1, 0);
    grid->addWidget(hot.G, 1, 1);
    grid->addWidget(cold.G, 1, 2);

    grid->addWidget(new QLabel("Температура входа, °C"), 2, 0);
    grid->addWidget(hot.t_in, 2, 1);
    grid->addWidget(cold.t_in, 2, 2);

    grid->addWidget(new QLabel("Температура выхода, °C"), 3, 0);
    grid->addWidget(hot.t_out, 3, 1);
    grid->addWidget(cold.t_out, 3, 2);

    auto hotBox = new QGroupBox("Свойства горячей среды");
    auto hotForm = new QFormLayout(hotBox);

    hot.t_avg = makeTempSB();
    hot.t_avg->setReadOnly(true);
    hot.t_avg->setFocusPolicy(Qt::NoFocus);
    hot.rho = makeRhoSB();
    hot.cp = makeCpSB();
    hot.lambda = makeLambdaSB();
    hot.viscosity = makeViscSB();
    hot.max_velocity = makeVeloSB();

    addRowWithUnit(hotForm, "Средняя температура", hot.t_avg, "°C");
    addRowWithUnit(hotForm, "Плотность", hot.rho, "кг/м³");
    addRowWithUnit(hotForm, "Теплоёмкость", hot.cp, "Дж/(кг·К)");
    addRowWithUnit(hotForm, "Теплопроводность", hot.lambda, "Вт/(м·К)");
    addRowWithUnit(hotForm, "Дин. вязкость", hot.viscosity, "мПа·с");
    addRowWithUnit(hotForm, "Макс. скорость", hot.max_velocity, "м/с");

    auto coldBox = new QGroupBox("Свойства холодной среды");
    auto coldForm = new QFormLayout(coldBox);

    cold.t_avg = makeTempSB();
    cold.t_avg->setReadOnly(true);
    cold.t_avg->setFocusPolicy(Qt::NoFocus);
    cold.rho = makeRhoSB();
    cold.cp = makeCpSB();
    cold.lambda = makeLambdaSB();
    cold.viscosity = makeViscSB();
    cold.max_velocity = makeVeloSB();

    addRowWithUnit(coldForm, "Средняя температура", cold.t_avg, "°C");
    addRowWithUnit(coldForm, "Плотность", cold.rho, "кг/м³");
    addRowWithUnit(coldForm, "Теплоёмкость", cold.cp, "Дж/(кг·К)");
    addRowWithUnit(coldForm, "Теплопроводность", cold.lambda, "Вт/(м·К)");
    addRowWithUnit(coldForm, "Дин. вязкость", cold.viscosity, "мПа·с");
    addRowWithUnit(coldForm, "Макс. скорость", cold.max_velocity, "м/с");

    auto wallBox = new QGroupBox("Материал стенки");
    auto wallForm = new QFormLayout(wallBox);

    wall.lambda = new CleanDoubleSpinBox;
    wall.lambda->setRangeWithWarning(10.0, 500.0, "Сталь: ~15-50, Медь: ~380 Вт/(м·К)");

    wall.fouling = new CleanDoubleSpinBox;
    wall.fouling->setDecimals(6);
    wall.fouling->setRangeWithWarning(0.0, 0.05, "Коэффициент загрязнения обычно крайне мал");

    addRowWithUnit(wallForm, "Теплопроводность", wall.lambda, "Вт/(м·К)");
    addRowWithUnit(wallForm, "Коэф. загрязнения", wall.fouling, "м²·К/Вт");

    layout->addWidget(balanceBox);
    layout->addWidget(hotBox);
    layout->addWidget(coldBox);
    layout->addWidget(wallBox);
    layout->addStretch();

    setupAutoCalc();
    updateAverageTemps();

    return w;
}

void CalcManagerWidget::setupAutoCalc()
{
    auto hook = [this](QDoubleSpinBox* s) {
        connect(s, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &CalcManagerWidget::onBalanceEdited);
        };

    hook(hot.G); hook(hot.t_in); hook(hot.t_out); hook(hot.cp);
    hook(cold.G); hook(cold.t_in); hook(cold.t_out); hook(cold.cp);
}

void CalcManagerWidget::onBalanceEdited()
{
    solveBalance();
    updateAverageTemps();
}

void CalcManagerWidget::solveBalance()
{
    double G1 = hot.G->value();
    double T1i = hot.t_in->value();
    double T1o = hot.t_out->value();
    double cp1 = hot.cp->value();

    double G2 = cold.G->value();
    double T2i = cold.t_in->value();
    double T2o = cold.t_out->value();
    double cp2 = cold.cp->value();

    int unknowns = 0;
    if (G1 <= 0) unknowns++;
    if (T1i == 0) unknowns++;
    if (T1o == 0) unknowns++;
    if (G2 <= 0) unknowns++;
    if (T2i == 0) unknowns++;
    if (T2o == 0) unknowns++;

    if (unknowns != 1) return;

    if (G1 > 0 && cp1 > 0 && T1i != 0 && T1o != 0) {
        double Q = G1 * cp1 * qAbs(T1i - T1o);

        if (T2o == 0 && G2 > 0 && cp2 > 0) {
            cold.t_out->blockSignals(true);
            cold.t_out->setValue(T2i + Q / (G2 * cp2));
            cold.t_out->blockSignals(false);
        }
        else if (T2i == 0 && G2 > 0 && cp2 > 0) {
            cold.t_in->blockSignals(true);
            cold.t_in->setValue(T2o - Q / (G2 * cp2));
            cold.t_in->blockSignals(false);
        }
        else if (G2 <= 0 && cp2 > 0 && qAbs(T2o - T2i) > 0.01) {
            cold.G->blockSignals(true);
            cold.G->setValue(Q / (cp2 * qAbs(T2o - T2i)));
            cold.G->blockSignals(false);
        }
    }
    else if (G2 > 0 && cp2 > 0 && T2i != 0 && T2o != 0) {
        double Q = G2 * cp2 * qAbs(T2o - T2i);

        if (T1o == 0 && G1 > 0 && cp1 > 0) {
            hot.t_out->blockSignals(true);
            hot.t_out->setValue(T1i - Q / (G1 * cp1));
            hot.t_out->blockSignals(false);
        }
        else if (T1i == 0 && G1 > 0 && cp1 > 0) {
            hot.t_in->blockSignals(true);
            hot.t_in->setValue(T1o + Q / (G1 * cp1));
            hot.t_in->blockSignals(false);
        }
        else if (G1 <= 0 && cp1 > 0 && qAbs(T1i - T1o) > 0.01) {
            hot.G->blockSignals(true);
            hot.G->setValue(Q / (cp1 * qAbs(T1i - T1o)));
            hot.G->blockSignals(false);
        }
    }
}

void CalcManagerWidget::updateAverageTemps()
{
    hot.t_avg->setValue((hot.t_in->value() + hot.t_out->value()) / 2.0);
    cold.t_avg->setValue((cold.t_in->value() + cold.t_out->value()) / 2.0);
}

QWidget* CalcManagerWidget::createGeometryTab()
{
    auto w = new QWidget;
    auto layout = new QVBoxLayout(w);
    auto box = new QGroupBox("Геометрия");
    auto form = new QFormLayout(box);

    auto makeChannelSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setRangeWithWarning(8.0, 25.0, "Ширина канала обычно от 8 до 25 мм");
        s->setDecimals(1);
        return s;
        };

    auto makeCoreSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setRangeWithWarning(150.0, 1000.0, "Внутренний диаметр обычно от 150 до 1000 мм");
        s->setDecimals(1);
        return s;
        };

    auto makeWallThickSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setRangeWithWarning(0.4, 30.0, "Толщина листа спирали обычно от 0.4 до 30 мм");
        s->setDecimals(1);
        return s;
        };

    geom.width_hot = makeChannelSB();
    geom.width_cold = makeChannelSB();
    geom.d_inner = makeCoreSB();
    geom.thickness_mm = makeWallThickSB();

    addRowWithUnit(form, "Ширина канала горячей среды", geom.width_hot, "мм");
    addRowWithUnit(form, "Ширина канала холодной среды", geom.width_cold, "мм");
    addRowWithUnit(form, "Внутренний диаметр спирали", geom.d_inner, "мм");
    addRowWithUnit(form, "Толщина стенки листа", geom.thickness_mm, "мм");

    auto widthBox = new QGroupBox("Ширина теплообменника");
    auto widthLayout = new QVBoxLayout(widthBox);

    geom.autoWidthCheck = new QCheckBox("Минимальная подходящая");
    geom.autoWidthCheck->setChecked(true);
    widthLayout->addWidget(geom.autoWidthCheck);

    auto makeWidthSB = []() {
        auto s = new CleanDoubleSpinBox;
        s->setRangeWithWarning(100.0, 1500.0,
            "Стандартные ширины: 400, 500, 700, 1000, 1100, 1250 мм");
        s->setDecimals(0);
        s->setSingleStep(50);
        s->setButtonSymbols(QAbstractSpinBox::NoButtons);
        return s;
        };

    geom.widthMin = makeWidthSB();
    geom.widthMax = makeWidthSB();
    geom.widthMin->setValue(400);
    geom.widthMax->setValue(1250);

    auto rangeWidget = new QWidget;
    auto rangeLayout = new QHBoxLayout(rangeWidget);
    rangeLayout->setContentsMargins(0, 0, 0, 0);
    rangeLayout->setSpacing(6);
    rangeLayout->addWidget(new QLabel("от"));
    rangeLayout->addWidget(geom.widthMin);
    rangeLayout->addWidget(new QLabel("мм  до"));
    rangeLayout->addWidget(geom.widthMax);
    rangeLayout->addWidget(new QLabel("мм"));
    rangeLayout->addStretch();
    widthLayout->addWidget(rangeWidget);

    rangeWidget->setEnabled(false);
    connect(geom.autoWidthCheck, &QCheckBox::toggled, this, [=](bool checked) {
        rangeWidget->setEnabled(!checked);
        });

    layout->addWidget(box);
    layout->addWidget(widthBox);
    layout->addStretch();
    return w;
}

void CalcManagerWidget::addRowWithUnit(QFormLayout* form, const QString& name, QDoubleSpinBox* spin, const QString& unit)
{
    auto container = new QWidget;
    auto hLayout = new QHBoxLayout(container);
    hLayout->addWidget(spin);
    auto l = new QLabel(unit);
    l->setFixedWidth(60);
    hLayout->addWidget(l);
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(4);
    form->addRow(name, container);
}

void CalcManagerWidget::setDefaults()
{
    this->blockSignals(true);

    hot.G->setValue(9.72);
    hot.t_in->setValue(90.0);
    hot.t_out->setValue(50.0);
    hot.rho->setValue(1160.0);
    hot.cp->setValue(3730.0);
    hot.lambda->setValue(0.667);
    hot.viscosity->setValue(0.373);
    hot.max_velocity->setValue(2.0);

    cold.G->setValue(15.7);
    cold.t_in->setValue(20.0);
    cold.t_out->setValue(40.0);
    cold.rho->setValue(997.0);
    cold.cp->setValue(4174.0);
    cold.lambda->setValue(0.578);
    cold.viscosity->setValue(0.715);
    cold.max_velocity->setValue(2.5);

    wall.lambda->setValue(45.0);
    wall.fouling->setValue(0.00036);

    geom.width_hot->setValue(12.0);
    geom.width_cold->setValue(12.0);
    geom.d_inner->setValue(300.0);
    geom.thickness_mm->setValue(4.0);
    geom.autoWidthCheck->setChecked(true);
    geom.widthMin->setValue(400);
    geom.widthMax->setValue(1250);

    this->blockSignals(false);
    updateAverageTemps();
}

Fluid CalcManagerWidget::toFluid(const FluidUI& ui)
{
    Fluid f;
    f.G = ui.G->value();
    f.t_in = ui.t_in->value();
    f.t_out = ui.t_out->value();
    f.rho = ui.rho->value();
    f.cp = ui.cp->value();
    f.lambda = ui.lambda->value();
    f.viscosity = ui.viscosity->value() / 1000.0;
    f.max_velocity = ui.max_velocity->value();
    return f;
}

Wall CalcManagerWidget::toWall(const WallUI& ui)
{
    Wall w;
    w.lambda = wall.lambda->value();
    w.thickness = geom.thickness_mm->value() / 1000.0;
    w.fouling_factor = wall.fouling->value();
    return w;
}

Geometry CalcManagerWidget::toGeometry(const GeometryUI& ui)
{
    Geometry g;
    g.width_hot = geom.width_hot->value() / 1000;
    g.width_cold = geom.width_cold->value() / 1000;
    g.d_inner = geom.d_inner->value() / 1000;
    g.cover_thickness = 0.020;
    g.shell_thickness = 0.040;

    g.auto_width = geom.autoWidthCheck->isChecked();
    g.width_min = geom.widthMin->value() / 1000.0;
    g.width_max = geom.widthMax->value() / 1000.0;

    return g;
}

void CalcManagerWidget::onCalculate()
{
    Fluid hotF = toFluid(hot);
    Fluid coldF = toFluid(cold);
    Wall wallM = toWall(wall);
    Geometry geomM = toGeometry(geom);

    SpiralHeatExchanger hx(hotF, coldF, wallM, geomM);

    CalculationResult result = hx.calculate();
    if (!result.error_message.empty()) {
        qDebug() << QString::fromStdString(result.error_message);
        return;
    }

    auto w = new ResultDialog({ result }, this);
    w->setWindowTitle("Результат расчета");
    w->resize(700, 400);
    w->show();

    connect(w, &ResultDialog::selectedResultConfirmed, this, [=](const CalculationResult& r) {
        buildModel(r);
        w->close();
        });
}

void CalcManagerWidget::buildModelFromResult(const CalculationResult& result) {
    buildModel(result);
}

void CalcManagerWidget::buildModel(const CalculationResult& result) {
    auto* progress = new QProgressDialog("Построение модели...", QString(), 0, 12, this);
    progress->setWindowTitle("Создание 3D-модели");
    progress->setWindowModality(Qt::WindowModal);
    progress->setMinimumDuration(0);
    progress->setAutoClose(false);
    progress->setAutoReset(false);
    progress->setCancelButton(nullptr);
    progress->setValue(0);
    progress->show();

    auto* thread = new QThread(this);
    auto* worker = new ModelBuildWorker(result);
    worker->moveToThread(thread);

    connect(worker, &ModelBuildWorker::progress, this,
        [progress](int step, int, const QString& desc) {
            progress->setValue(step);
            progress->setLabelText(desc);
        }, Qt::QueuedConnection);

    connect(worker, &ModelBuildWorker::finished, this,
        [this, progress, thread](SPtr<MbAssembly> assembly) {
            progress->setValue(progress->maximum());
            progress->close();
            progress->deleteLater();

            if (m_viewport)
                m_viewport->displayModel(assembly);

            thread->quit();
        }, Qt::QueuedConnection);

    connect(thread, &QThread::started, worker, &ModelBuildWorker::run);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}