#include <QtGui/QApplication>
#include "mainwindow.h"
//#include "Interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Interface i;

    w.show();

    return a.exec();
}
