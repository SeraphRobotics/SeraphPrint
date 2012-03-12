#include <QtGui/QApplication>
#include "mainwindow.h"
//#include "Interface.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QSettings setup. These values will carry over in the rest of the application.
    QCoreApplication::setOrganizationName("Seraph");
    QCoreApplication::setOrganizationDomain("seraphrobotics.com");
    QCoreApplication::setApplicationName("SeraphPrint");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    // Default scope is QSettings::UserScope

    // This is the list of values the application is storing:
    //   config_dir
    //   load config next time index
    //   last used fab file


    MainWindow w;

    QString cmd;
    QString arg;

    for(int i=0;i<argc;i++){
        cmd = argv[i];
        cmd.replace(" ","");
        if (("-file"==cmd)||("-f"==cmd)){
            arg = argv[i+1];
            w.setFileArg(arg);
        }
    }

    w.show();

    return a.exec();
}
