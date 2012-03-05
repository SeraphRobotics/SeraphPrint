#include <QtGui/QApplication>
#include "mainwindow.h"
//#include "Interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QSettings setup. These values will carry over in the rest of the application.
    QCoreApplication::setOrganizationName("FabAtHome");
    QCoreApplication::setOrganizationDomain("fabathome.org");
    QCoreApplication::setApplicationName("FabPrint");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    // Default scope is QSettings::UserScope

    // This is the list of values the application is storing:
    //   config_dir
    //   load config next time index
    //   last used fab file

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
