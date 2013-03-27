#include "vmtester.h"
#include <QDebug>

VMTester::VMTester(){
    configFilePath="../../../media/blash-lead.config";
    comport="COM3";
}

bool VMTester::connectVM(){
        if(vm.isInitialized()){return vm.isInitialized();}

        //load the config file into the DOM document
        QDomDocument document;
        {
          QFile configFile(configFilePath);
          if (!configFile.open(QFile::ReadOnly)) {
              qDebug()<<"\nFAILED TO OPEN CONFIG FILE\n";
              return false;
          }
          document.setContent(&configFile);
          configFile.close();
        }
        vm.setComPort(comport);
        vm.loadConfig(document);// Load the config into the VM to create the electronics
        qDebug()<<"loaded";
        return vm.isInitialized();

}

bool VMTester::movementTest(){
    if(!vm.isInitialized()){
        qDebug()<< "not initialized";
        return false;
    }
    int statesize = vm.nstatesize();
    float revPerY = 0.0331572798;
    float revPerX = 0.028148728;

    float dx = 20; //mm
    float dy = 20; //mm
    float dz = 0;  //mm
    float y = dy*revPerY;
    float x = dx*revPerX;
    float z = 0;
    float t = 1;

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



    NPath p1(statesize);
    p1.addState(v1);
    p1.addState(v2);
    p1.addState(v3);
    p1.addState(v4);

    return vm.executeNPath(p1);
}

