#include "ThemeManager.h"
#include <QApplication>

void ThemeManager::apply(Theme theme)
{
    QString qss;

    switch (theme)
    {
    case Theme::Light:
        qss = lightTheme();
        break;
    case Theme::Dark:
        qss = darkTheme();
        break;
    }

    qApp->setStyleSheet(qss);
}

QString ThemeManager::lightTheme()
{
    return R"(
        QWidget {
            background-color: #f5f5f5;
            color: #111;
        }

        QMenuBar {
            background-color: #ffffff;
        }

        QMenu {
            background-color: #ffffff;
        }
    )";
}

QString ThemeManager::darkTheme()
{
    return R"(
        QWidget {
            background-color: #1e1e1e;
            color: #dddddd;
        }

        QMenuBar {
            background-color: #2b2b2b;
        }

        QMenu {
            background-color: #2b2b2b;
        }

        QSplitter::handle {
            background-color: #444;
        }
    )";
}