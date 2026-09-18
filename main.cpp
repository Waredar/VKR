#include <QApplication>
#include <QWindow>
#include <QStyleFactory>
#include <qstyle.h>
#include <QPixmap>
#include <QPainter>
#include <QSvgRenderer>
#include "AppWindow.h"
#include <vsn_application.h>

int main(int argc, char* argv[])
{
    qputenv("QT_QPA_PLATFORM", "windows:darkmode=0");

    QApplication app(argc, argv);
    VSN::Application vapp;

    QSvgRenderer renderer(QString(":/logo.svg"));
    if (renderer.isValid()) {
        QPixmap pixmap(256, 256);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        renderer.render(&painter);
        app.setWindowIcon(QIcon(pixmap));
    }

    int result = 0;

    {
        AppWindow win;
        win.showMaximized();

        result = app.exec();
    }

    return result;
}