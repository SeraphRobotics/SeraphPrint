#include "virtualmachines.h"
#include <stdio.h>
#include <QCoreApplication>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

#include "../../JrkerrElectronics/nmotion.h"
#include "../../JrkerrElectronics/npath.h"
#include "testing/util.h"
#include "testing/unittests.h"

#include "coreinterface.h"
#include "testing/testerforci.h"
#include "testing/jscitest.h"
#include "testing/vmtester.h"
#include "comportdetector.h"

int main(int argc, char *argv[]) {
    printf("\nStarting..");
    QCoreApplication app(argc,argv);

    VMTester vmtest;
    bool worked = vmtest.connectVM();
    printf("\n it %s work\n", (worked)?"did":"didnt");
//    vmtest.NPathTest();
    vmtest.moveTest();




    //testNPaths(&vm);
    //testScripting(&vm);
    //testVoxels(&vm);
    //testXDFLPaths(&vm);
    //testXDFLParsing(&vm);
    //vm.dumpstates();


//    testerforci *tester = new testerforci();
//    QTimer::singleShot(0,tester,SLOT(setConfig()));

//    JsCiTest *jstester = new JsCiTest();
//    QTimer::singleShot(0,jstester,SLOT(test()));

//    ComportDetector *cpi = new ComportDetector();
    vmtest.vm.eInterface.waitOnMove();
    QTimer::singleShot(100,&app,SLOT(quit()));
    return app.exec();
}
