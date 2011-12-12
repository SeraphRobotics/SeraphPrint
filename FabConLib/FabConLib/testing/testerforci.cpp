#include "testerforci.h"

testerforci::testerforci():connected_(false){
    ci = new CoreInterface();
    makeConnections();

}

testerforci::testerforci(CoreInterface* coreinterface):connected_(false){
    ci = coreinterface;
    makeConnections();
}


void testerforci::makeConnections(){
    connect(ci,SIGNAL(currentPosition(double,double,double)),this,SLOT(updatedPosition(double,double,double)));
    connect(ci,SIGNAL(moving()),this,SLOT(moving()));
    connect(ci,SIGNAL(stateChaged(int)),this,SLOT(chagedState(int)));
    connect(ci,SIGNAL(estimated(double,double)),this,SLOT(estimated(double,double)));
    connect(ci,SIGNAL(materialsAvailable(QMap<int,Material>)),this,SLOT(materialsAvailable(QMap<int,Material>)));
    connect(ci,SIGNAL(bayMaterial(int,int)),this,SLOT(bayMaterial(int,int)));
    connect(ci,SIGNAL(currentCommand(int)),this,SLOT(currentCommand(int)));
    connect(ci,SIGNAL(needMaterialLoaded(int)),this,SLOT(needMaterialLoaded(int)));
}


void testerforci::setConfig(){
    printf("\nattemping to make a connection...");
    QString configFilePath="../../../media/JrKerr-Single-deposition.config";
    QDomDocument document;
    {
      QFile configFile(configFilePath);
      if (!configFile.open(QFile::ReadOnly)) {
          printf("\nFAILED TO OPEN CONFIG FILE\n");
          return;
      }
      document.setContent(&configFile);
      configFile.close();
    }
    ci->setConfig(document.toString(),"COM3");
}

void testerforci::chagedState(int state){
    if ((state== CoreInterface::Connected)&&!connected_){
        printf("\nstate is connected");
        connected_=true;
//        ci->move(0,-80,0,80);
//        disconnect(ci,SIGNAL(currentPosition(double,double,double)),this,SLOT(updatedPosition(double,double,double)));
        loadXDFL();
    }else if (state == CoreInterface::FileLoaded){
        printf("\nfile loaded");
        int materialid =1;
        int bayid = 0;
        ci->setMaterial(bayid,materialid);
//        ci->requestBayMaterial(0);
//        ci->resetPosition();
        ci->startPrint();
    }else if(state ==CoreInterface::Printing){
//        ci->move(100,0,0,100);
//
        printf("\nPRINTING");
        QTimer::singleShot(1000,ci,SLOT(pausePrint()));
        QTimer::singleShot(15000,ci,SLOT(resumePrint()));
//        QTimer::singleShot(9000,ci,SLOT(cancelPrint()));
    }
}

void testerforci::updatedPosition(double x, double y, double z){
    printf("\nNew Position is %f,%f,%f",x,y,z);
}
void testerforci::moving(){
    printf("\nmoving");
}

void testerforci::loadXDFL(){
    QDomDocument xdflDom;
    QString xdflFilePath="../../../media/testxdfl-mid.xdfl";
    // load the XDFL file into the DOM document
    {
      QFile xdflFile(xdflFilePath);
      if (!xdflFile.open(QFile::ReadOnly)) {
          printf("\nFAILED TO OPEN XDFL FILE\n");
          return;
      }
      xdflDom.setContent(&xdflFile);
      xdflFile.close();
    }
    ci->setXDFL(xdflDom.toString());


}

void testerforci::estimated(double t, double v){
    printf("\nTime = %f\tVolume = %f",t,v);
}

void testerforci::materialsAvailable(QMap<int,Material> ms){
    materials_ = ms;
    printf("\nThe following materials are avalible");
    QMapIterator<int,Material> i(ms);
    while(i.hasNext()){
        i.next();
        printf("\n\t%s, id:%i",i.value().name.toStdString().c_str(),i.key());
    }
}

void testerforci::bayMaterial(int bayid, int materialid){
    printf("\nbay %i is equiped with material %s with id %i",bayid,
           materials_[materialid].name.toStdString().c_str(),materialid);
}

void testerforci::currentCommand(int cmd){
    printf("\nCurrent command is %i",cmd);
}

void testerforci::needMaterialLoaded(int i){
    printf("\nNeed Material id:%i %s",i,materials_[i].name.toStdString().c_str());
}
