#include "coreinterface.h"

#include "loadconfigthread.h"

#include <stdio.h>
#include <QApplication>
#include <QDebug>

CoreInterface::CoreInterface():state_(NotInitialized){
    vm_ = new VirtualPrinter();
}


void CoreInterface::setState(SystemState s){
    state_=s;
    stateChaged((int)s);
}


void CoreInterface::setConfig(QString configFile,QString comport){

    // load the config file into the DOM document
    QDomDocument document;
    document.setContent(configFile);
    if(""!=comport){vm_->setComPort(comport);}


    LoadConfigThread* configthread = new LoadConfigThread(vm_,document);
    connect(configthread,SIGNAL(loaded()),this,SLOT(configLoaded()));
    connect(configthread,SIGNAL(finished()),configthread,SLOT(deleteLater()));
    vm_->moveToThread(configthread);
    QTimer::singleShot(0,configthread,SLOT(start()));
}


void CoreInterface::resetPosition(){
    if((state_==NotInitialized) || (state_==Printing)){
        emit outOfStateCall();
        return;
    }
    vm_->resetPosition();
    getCurrentPosition();
}

void CoreInterface::moveTo(double x, double y, double z, double speed){
    if((state_==NotInitialized) || (state_==Printing)){
        emit outOfStateCall();
        return;
    }
    qDebug()<<"moving";
    emit moving();
    vm_->moveTo(x,y,z,speed);
//    getCurrentPosition();
}

void CoreInterface::move(double x, double y, double z, double speed){
    if((state_==NotInitialized) || (state_==Printing)){
        emit outOfStateCall();
        return;
    }
    emit moving();
    vm_->move(x,y,z,speed);
    getCurrentPosition();
}
 QVector<double> CoreInterface::getCurrentPosition(){
     if ((state_==NotInitialized)||(state_==Printing)){return QVector<double>(3,0);}
     QVector<double> p = vm_->currentPosition();
     emit currentPosition(p.at(0),p.at(1),p.at(2));
     return p;
 }


void CoreInterface::setXDFL(QString xdfl){
    if(state_!=Connected){
        emit outOfStateCall();
        return;
    }

    QDomDocument document;
    document.setContent(xdfl);
    handler_ = new XDFLHandler(vm_,document);
    connect(handler_,SIGNAL(finished()),this,SLOT(donePrinting()));
    connect(handler_,SIGNAL(destroyed()),this,SLOT(donePrinting()));
    connect(handler_,SIGNAL(terminated()),this,SLOT(donePrinting()));
    connect(handler_,SIGNAL(finished()),handler_,SLOT(deleteLater()));
    connect(handler_,SIGNAL(startingCommand(int)),this,SLOT(processingCommand(int)));
    connect(handler_,SIGNAL(needMaterialChange(int)),this,SLOT(needMaterial(int)));
    // Make other needed connections here

    //everything here after should be handled by a seperate slot called by the xdflhandler while its running but not printing.
    double t = handler_->getEstimatedTime();
    double v = handler_->getEstimatedVolume();
    int numCommands = handler_->getNumberOfCommands();
    emit estimated(t,v,numCommands);
    idMaterialMap_ = handler_->getMaterials();
    emit materialsAvailable(idMaterialMap_);
    // Goes at the end
    setState(FileLoaded);

}

void CoreInterface::requestBayMaterial(int bayid){
    if ((state_!=FileLoaded) && (state_!= Printing)){
        emit outOfStateCall();
        return;
    }
    int materialid = vm_->bays[bayid]->getMaterial().id;
    emit bayMaterial(bayid, materialid);
}
void CoreInterface::setMaterial(int bayid,int materialid){
    if ((state_!=FileLoaded) && (state_!= Printing)){
        emit outOfStateCall();
        return;
    }
    if((bayid>(vm_->bays.size()+1)) || !(idMaterialMap_.contains(materialid))){ // TODO: there should be a check for bayid validity here
        return;
    }
    Material m = idMaterialMap_[materialid];
    vm_->bays[bayid]->setMaterial(m);
    emit bayMaterial(bayid, materialid);



}
void CoreInterface::moveBayMotor(int bayid, double amount, double time){
    if ((state_==NotInitialized) || (state_==Printing)){return;}
    // THIS SUCKS we need to rethink this
    qDebug()<<"Ordered Bay to Move";
    vm_->bays[bayid]->jogActuators(amount,time);
}

void CoreInterface::startPrint(){
    if (state_!=FileLoaded){return;}
//    positionTimer_.disconnect();
//    positionTimer_.setInterval(10000000);
    vm_->moveToThread(handler_);
    setState(Printing);
    QTimer::singleShot(0,handler_,SLOT(start()));
}

void CoreInterface::pausePrint(){
    QTimer::singleShot(0,handler_,SLOT(pause()));
}

void CoreInterface::resumePrint(){
    QTimer::singleShot(0,handler_,SLOT(resume()));
}

void CoreInterface::cancelPrint(){
    QTimer::singleShot(0,handler_,SLOT(cancel()));

}

void CoreInterface::forceStop(){
    vm_->forceStop();
//    positionTimer_.disconnect();
    setState(NotInitialized);
}


void CoreInterface::processingCommand(int i){
    emit currentCommand(i);
}

void CoreInterface::needMaterial(int i){
//    pausePrint();
    emit needMaterialLoaded(i);

}

void CoreInterface::configLoaded(){
    setState(Connected);
    getCurrentPosition();
//    connect(&positionTimer_,SIGNAL(timeout()),this,SLOT(getCurrentPosition()));
//    positionTimer_.setInterval(1000);
//    positionTimer_.start();
}

void CoreInterface::donePrinting(){
//    setState(Connected);
//    getCurrentPosition();
    configLoaded();
    emit printsComplete();
}
