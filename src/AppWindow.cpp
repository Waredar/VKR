#include "AppWindow.h"
#include "LicenseManager.h"
#include "LicenseDialog.h"
#include "CalcSceneWidget.h"
#include "CalcManagerWidget.h"
#include "CalcResultSerializer.h"
#include "ResultDialog.h"

#include <QApplication>
#include <QWindow>
#include <QMessageBox>
#include <QSplitter>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QTimer>
#include <QFileDialog>
#include <QFileInfo>
#include <QActionGroup>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QSvgRenderer>

#include <system_atomic.h>
#include <action_solid.h>
#include <action_shell.h>
#include <assembly.h>
#include <topology_iterator.h>
#include <instance_item.h>
#include <space_instance.h>
#include <plane_instance.h>
#include <reference_item.h>
#include <surface.h>
#include <solid.h>
#include <wire_frame.h>
#include <point_frame.h>
#include <cur_polyline.h>
#include <conv_model_exchange.h>
#include <conv_exchange_settings.h>
#include <conv_model_document.h>
#include <conv_requestor.h>
#include <attr_color.h>
#include <attr_common_attribute.h>
#include <check_geometry.h>
#include <alg_draw.h>
#include <list>
#include <sstream>
#include <stdio.h>
#include <last.h>




AppWindow::AppWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("SpiralHX");

    QSvgRenderer renderer(QString(":/logo.svg"));
    if (renderer.isValid()) {
        QPixmap pixmap(256, 256);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);
        setWindowIcon(QIcon(pixmap));
    }

    checkLicense();

    setupUi();

}

void AppWindow::checkLicense()
{
    if (m_licenseManager.activateFromFile())
    {
        return;
    }

    while (true)
    {
        LicenseDialog dlg(this);

        if (dlg.exec() != QDialog::Accepted)
        {
            QApplication::quit();
            return;
        }

        auto result = m_licenseManager.activate(
            dlg.key(),
            dlg.signature()
        );

        if (result == LicenseManager::Result::Success)
            return;

        QMessageBox::warning(this, "Активация лицензии", "Ошибка активации лицензии");
    }
}

void AppWindow::setupUi()
{
    auto fileMenu = menuBar()->addMenu("Файл");
    auto openCalcAction = fileMenu->addAction("Открыть расчёт...");
    auto saveStlAction = fileMenu->addAction("Сохранить модель");

    connect(openCalcAction, &QAction::triggered,
        this, &AppWindow::onOpenCalc);
    connect(saveStlAction, &QAction::triggered,
        this, &AppWindow::onSaveModel);

    auto viewMenu = menuBar()->addMenu("Вид");
    auto planeMenu = viewMenu->addMenu("Сечение модели");

    auto actX = planeMenu->addAction("По оси X");
    auto actY = planeMenu->addAction("По оси Y");
    auto actZ = planeMenu->addAction("По оси Z");

    QList<QAction*> actions = { actX, actY, actZ };

    for (auto act : actions) {
        act->setCheckable(true);

        connect(act, &QAction::triggered, this, [this, act, actions]() {
            if (!act->isChecked()) {
                m_viewport->togglePlaneCutting(false);
            }
            else {
                for (auto other : actions) {
                    if (other != act) {
                        other->blockSignals(true);
                        other->setChecked(false);
                        other->blockSignals(false);
                    }
                }

                CuttingPlane plane = CuttingPlane::Y;
                if (act->text().contains("X")) plane = CuttingPlane::X;
                else if (act->text().contains("Z")) plane = CuttingPlane::Z;

                m_viewport->togglePlaneCutting(true, plane);
            }
            });
    }

    auto central = new QWidget(this);
    setCentralWidget(central);


    m_splitter = new QSplitter(Qt::Horizontal, central);

    m_viewport = new CalcSceneWidget(m_splitter);
    m_sidePanel = new CalcManagerWidget(m_splitter);
    m_sidePanel->setViewport(m_viewport);

    auto layout = new QHBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_splitter);

    m_splitter->setStretchFactor(0, 4);
    m_splitter->setStretchFactor(1, 1);

    QTimer::singleShot(0, this, [this]()
        {
            int w = this->width();
            if (w <= 0) w = 1200;

            m_splitter->setSizes({ int(w * 0.75), int(w * 0.25) });
        });


    resize(1400, 900);
    setMinimumSize(1100, 700);
}

void AppWindow::showEvent(QShowEvent* event) {
    windowHandle()->setSurfaceType(QWindow::OpenGLSurface);
}

void AppWindow::onSaveModel()
{
    SPtr<MbAssembly> assembly = m_viewport->getAssembly();

    if (!assembly) {
        QMessageBox::warning(this, "Сохранение", "Нет модели для сохранения.");
        return;
    }

    QStringList filters;
    filters
        << "File C3D (*.c3d)"
        << "File OBJ (*.obj)"
        << "File ACISC (*.sat)"
        << "File STEP (*.step *.stp)"
        << "File PARASOLID (*.x_b)"
        << "File JT (*.jt *.JT)"
        << "File STL (*.stl *.STL)";

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Сохранить модель как...",
        "",
        filters.join(";;")
    );

    if (fileName.isEmpty())
        return;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    MbModel model;
    model.AddItem(*assembly);

    MbeConvResType result = c3d::ExportIntoFile(
        model,
        c3d::WToPathstring(fileName.toStdWString())
    );

    QApplication::restoreOverrideCursor();

    if (result == cnv_Success) {
        QMessageBox::information(this, "Успех", "Файл успешно сохранен.");
    }
    else {
        QMessageBox::critical(
            this,
            "Ошибка",
            QString("Не удалось сохранить файл. Код ошибки C3D: %1")
            .arg(static_cast<int>(result))
        );
    }
}

void AppWindow::onOpenCalc()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        "Открыть расчёт",
        {},
        "Файл расчёта SpiralHX (*.txt)"
    );
    if (path.isEmpty())
        return;

    QString err;
    CalculationResult res = CalcResultSerializer::load(path, err);
    if (!err.isEmpty()) {
        QMessageBox::critical(this, "Ошибка открытия", err);
        return;
    }

    auto* dlg = new ResultDialog(res, this);
    dlg->setWindowTitle("Результат расчёта — " + QFileInfo(path).fileName());
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->show();

    connect(dlg, &ResultDialog::selectedResultConfirmed,
        this, [this](const CalculationResult& r) {
            m_sidePanel->buildModelFromResult(r);
        });
}