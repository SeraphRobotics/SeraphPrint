#include "loadconfigthread.h"
#include <QCoreApplication>
#include <QApplication>
#include <stdio.h>
LoadConfigThread::LoadConfigThread():ready_(false)
{
}


LoadConfigThread::LoadConfigThread(VirtualPrinter* vm,QDomDocument config):ready_(false){
    setVM(vm);
    setConfig(config);
}
void LoadConfigThread::setVM(VirtualPrinter* vm){
    vm_ = vm;
    vmThread_ = vm->thread();
    checkReady();
}

void LoadConfigThread::setConfig(QDomDocument config){
    config_ = config;
    checkReady();
}

void LoadConfigThread::checkReady(){
    if (!vm_->isInitialized() &&config_.isNull()){//
        ready_ = true;
        emit ready();
    }

}

void LoadConfigThread::run(){
    checkReady();
    if (ready_){
        vm_->loadConfig(config_);
        vm_->moveToThread(QApplication::instance()->thread());
        if(vm_->isInitialized()){
            emit loaded();
        }

    }else{
        vm_->moveToThread(QApplication::instance()->thread());
    }
}
