#pragma once

#include <QMainWindow>
#include "LicenseManager.h"
#include "solid.h"

class CalcSceneWidget;
class CalcManagerWidget;
class QSplitter;


class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget* parent = nullptr);

private:
    void checkLicense();
    void setupUi();
    void onSaveModel();
    void onOpenCalc();

protected:
    void showEvent(QShowEvent* event) override;

private:
    LicenseManager m_licenseManager;
    QSplitter* m_splitter = nullptr;
    CalcSceneWidget* m_viewport = nullptr;
    CalcManagerWidget* m_sidePanel = nullptr;
};