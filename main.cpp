#include "mainwindow.h"
#include "data.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    initialize();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
