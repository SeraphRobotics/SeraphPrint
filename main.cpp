#include <QtGui/QApplication>
#include "mainwindow.h"
//#include "Interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Interface i;

    /*QString passed_file;

    if(argc == 2)
    {
        passed_file = argv[1];
        qDebug() << "Argument received " << passed_file << endl;
        w.setFileArg(passed_file);
        w.setUseFileArg(true);
    }*/
    w.show();

    return a.exec();
}
