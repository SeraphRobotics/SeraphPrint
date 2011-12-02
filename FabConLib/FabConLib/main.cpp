#include "virtualmachines.h"
#include <stdio.h>
#include <QCoreApplication>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

#include "nmotion.h"
#include "npath.h"
#include "util.h"
#include "unittests.h"

int main(int argc, char *argv[]) {

    QCoreApplication app(argc,argv);

    TestPrinter vm;
//   VirtualPrinter vm;
    QString configFilePath="../../../media/testConfig.config";
//    QString ComPort="";   //"tty.usbserial-A9003UF2";


    QDomDocument document;

    // load the config file into the DOM document
    {
      QFile configFile(configFilePath);
      if (!configFile.open(QFile::ReadOnly)) {
          printf("\nFAILED TO OPEN CONFIG FILE\n");
          return app.exec();
      }
      document.setContent(&configFile);
      configFile.close();
    }
    vm.loadConfig(document);// Load the config into the VM to create the electronics
    if (vm.isInitialized()){
        printf("\nmoving motor!@!!!!");
//        vm.eInterface.getCoordinatedMotion()->initializePathMode();
    }


//    testNPaths(&vm);
//    testScripting(&vm);
//    testVoxels(&vm);
//    testXDFLPaths(&vm);
    testXDFLParsing(&vm);

    //Need to wait here
    vm.thread()->wait();

    vm.dumpstates();
    printf("\nAfter dumping states");
    fflush(stdout);
    //vm.eInterface.waitOnMove();
    printf("\nErrors: %s",vm.getErrors().toStdString().c_str());
    fflush(stdout);
    //vm.eInterface.reset();

    printf("\nDone\n");
    fflush(stdout);
    app.exit(true);
    return app.exec();//return 0;

}


