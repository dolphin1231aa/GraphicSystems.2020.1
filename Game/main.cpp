#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QMovie>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    qApp->setStyleSheet("QMessageBox QPushButton { font-size: 18px; padding: 10px; border: 1px solid #4d4d4d;}");

    w.show();

    return app.exec();
}
