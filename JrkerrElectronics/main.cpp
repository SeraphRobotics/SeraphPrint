#include <stdio.h>
#include <QCoreApplication>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include "nmotion.h"
#include "npath.h"
#include "electronicsinterface.h"
#include <QDebug>


int main(int argc, char *argv[]) {
    QCoreApplication app(argc,argv);
    QString configFilePath= "JrKerr-Single-deposition.config"; //hobby-servo.config";   //"./testConfig.config";
    QString ComPort="COM3"; ///dev/tty.usbserial-A400gNfH";   //"tty.usbserial-A9003UF2";
    ElectronicsInterface eInterface;
    QDomDocument document;
    // load the config file into the DOM document
    {
        QFile configFile(configFilePath);
        if (!configFile.open(QFile::ReadOnly)) {
            printf("\nFAILED TO OPEN CONFIG FILE\n");
            app.exec();
        }
        document.setContent(&configFile);
        configFile.close();
    }
    // Load the config to create the electronics
    QDomElement root = document.documentElement();
    QDomNode electronics = root.namedItem("electronics");
    //initialized the electronics
    QString result = eInterface.initialize(electronics,ComPort);
    printf("\ninitialization results %s\n",result.toStdString().c_str());
    if (eInterface.isInitialized()){
        printf("\nmoving motor!@!!!!");
        // eInterface.getCoordinatedMotion()->initializePathMode();
        // eInterface.getMotor(1)->moveAbsolute(.1,.1,.1);
        // eInterface.getMotor(1)->waitMove();*/

        CoordinatedMotion* cmotion = eInterface.getCoordinatedMotion();
       int statesize=cmotion->getNumberOfAxes()+1;

       float revPerY = 0.0331572798;
       float revPerX = 0.028148728;

       float dx = 20; //mm
       float dy = 20; //mm
       float dz = 0;  //mm
       float y = dy*revPerY;
       float x = dx*revPerX;
       float z = 0;
       float t = 3;

        State v1(statesize,0);
        v1[0]=t;
        v1[1]=x;
        v1[2]=0;
        v1[3]=0;

        State v2(statesize,0);
        v2[0]=t;
        v2[1]=x;
        v2[2]=y;
        v2[3]=0;

        State v3(statesize,0);
        v3[0]=t;
        v3[1]=0;
        v3[2]=y;
        v3[3]=0;

        State v4(statesize,0);
        v4[0]=t;
        v4[1]=0;
        v4[2]=0;
        v4[3]=0;

//        State v5(statesize,0);
//        v5[0]=t;
//        v5[1]=x;
//        v5[2]=y;
//        v5[3]=z;


        NPath p1(statesize);
        p1.addState(v1);
        p1.addState(v2);
        p1.addState(v3);
        p1.addState(v4);
//        p1.addState(v5);


        if (cmotion->initializePathMode()){
            printf("\ntrying coordinated motion");
//            cmotion->applyBacklash(p1);
            cmotion->moveAlongPath(p1);
        }
    }
    eInterface.waitOnMove();
    printf("\nErrors: %s",eInterface.getErrors().toStdString().c_str());
    eInterface.reset();
    printf("\nDone\n");
    return 0;
//    app.exit(true);
//    return app.exec();//return 0;
}
