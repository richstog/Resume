#include "mainwindow.h"

#include <QApplication>
//#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //int ScreenHeight = QApplication::desktop()->availableGeometry().height() * 0.95;
    w.setMinimumSize((600 + 430), 600);
    w.setMaximumSize((600 + 430), 600);
    w.setGeometry(0, 0, (600 + 430), 600);
    w.Resize();
    w.show();
    return a.exec();
}
