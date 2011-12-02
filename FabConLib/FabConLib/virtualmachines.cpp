#include "virtualmachines.h"
#include <stdio.h>
#include <QTextStream>
#include <QFile>
#include "jsnpath.h"
#include <stdio.h>

#include "util.h"
#include "xdflvoxel.h"

VMPrototype::VMPrototype():comPort_(""),error_string_(""),initialized_(false),statesize_(0){
}


bool VMPrototype::isInitialized(){
    return initialized_;
}


int VMPrototype::nstatesize(){
    return statesize_;
}

void VMPrototype::setComPort(QString comPort){
    if (!comPort.isNull()){comPort_=comPort;}
}

QString VMPrototype::getErrors(){
    return error_string_;
}

bool VMPrototype::executeNPath(NPath path){
    printf("wtf");
    return true;
}

QScriptEngine* VMPrototype::makeEngine(){

    QScriptEngine* engine = new QScriptEngine;

    //Add XYZMotion to engine_

    QScriptValue scriptXYZ = engine->newQObject(&jsxyz_);
    engine->globalObject().setProperty("xyz",scriptXYZ);

    // State object
    int statesize = nstatesize();
    engine->globalObject().setProperty("statesize",statesize);
    QScriptValue stateProto = engine->newArray(statesize);
    for(int j=0;j<statesize;j++){
        stateProto.setProperty(j,0);
    }
    stateProto.setProperty("distance", 0);
    engine->globalObject().setProperty("State", engine->newFunction(newJsState,stateProto));

    QScriptValue npathProto = engine->newArray(0);
    engine->globalObject().setProperty("NPath",engine->newFunction(newJsNPath,npathProto));

    return engine;
}


void VMPrototype::loadConfig(QDomDocument document){



    QDomElement root = document.documentElement();

    //BAYS
    QDomNode tools = root.namedItem("tool");
    QDomNodeList toolChildren  = tools.childNodes();
    for(int k=0; k<toolChildren.length();k++){
        if ("bay"==toolChildren.at(k).nodeName().toLower()){
            bays.append(new Bay(toolChildren.at(k)));
            bays.last()->setIdMap(idtostatemap_);
            bays.last()->setEngine(makeEngine());
        }
    }

    // XYZMOTION
    QDomNode motion = root.namedItem("motion");
    xyzmotion =new XYZMotion(motion);
    xyzmotion->setFrequency(frequency_);
    xyzmotion->setIdMap(idtostatemap_);
    jsxyz_.setXYZ(xyzmotion);


}






VirtualPrinter::VirtualPrinter():VMPrototype()
{
}


void VirtualPrinter::loadConfig(QDomDocument document){

    QDomElement root = document.documentElement();
    QDomNode electronics = root.namedItem("electronics");


    // EINTERFACE specific
    //initialized the electronics
    eInterface.initialize(electronics,comPort_);
    initialized_=eInterface.isInitialized();
    idtostatemap_ = eInterface.getCoordinatedMotion()->getIdToStateIndexMap();
    frequency_ = eInterface.getCoordinatedMotion()->getFrequency();
    statesize_ = eInterface.getCoordinatedMotion()->getNumberOfAxes()+1;




    //BAYS
    QDomNode tools = root.namedItem("tool");
    QDomNodeList toolChildren  = tools.childNodes();
    for(int k=0; k<toolChildren.length();k++){
        if ("bay"==toolChildren.at(k).nodeName().toLower()){
            bays.append(new Bay(toolChildren.at(k)));
            bays.last()->setIdMap(idtostatemap_);
            bays.last()->setEngine(makeEngine());
        }
    }

    // XYZMOTION
    QDomNode motion = root.namedItem("motion");
    xyzmotion =new XYZMotion(motion);
    xyzmotion->setFrequency(frequency_);
    xyzmotion->setIdMap(idtostatemap_);
    jsxyz_.setXYZ(xyzmotion);
}



QString VirtualPrinter::getErrors(){

    QString returnstring = "";
    QTextStream ss(&returnstring,QIODevice::WriteOnly);
    foreach(Motor* m,eInterface.getMotors()){
        ss<<"\nMotor "<<m->getID()<<":"<<m->getErrors();
    }
    foreach(Bay* b,bays){
        ss<<"\nBay "<<b->getId()<<":"<<b->getErrors();
    }
    ss<<"\nCMotion:"<<eInterface.getCoordinatedMotion()->getErrors();
    ss<<"\nVM:"<<error_string_;


    return returnstring;
}

bool VirtualPrinter::executeNPath(NPath path){
    if(!initialized_){return false;}
    eInterface.getCoordinatedMotion()->initializePathMode();
    return eInterface.getCoordinatedMotion()->moveAlongPath(path);
}



TestPrinter::TestPrinter():VMPrototype(){}


void TestPrinter::loadConfig(QDomDocument document){
//    QDomElement root = document.documentElement();
//    QDomNode electronics = root.namedItem("electronics");

    // THIS SHOULD BE BASED ON THE NODES
    frequency_ = 30;
    idtostatemap_.clear();
    idtostatemap_[0]=1;
    idtostatemap_[1]=2;
    idtostatemap_[2]=3;
    idtostatemap_[3]=4;
    statesize_ = 5;
    //totalprintcommands_ = NPath(statesize_,false);
    VMPrototype::loadConfig(document);




}



bool TestPrinter::executeNPath(NPath path){
    path.toAbsolute();
//    for(int i=0;i<path.numberOfStates();i++){
//        totalprintcommands_.addState(path.getState(i));
//    }
    totalprintcommands_.append(path);
}

void TestPrinter::dumpstates(){
    printf(QString::number(totalprintcommands_.size()).toStdString().c_str());
    for(int i=0;i<totalprintcommands_.size();i++){
        QString s("");
        QTextStream ss(&s,QFile::WriteOnly);
        ss<<"Total"<<i;
        test(s,totalprintcommands_.at(i));
    }

}





QString runScript(VirtualPrinter *vm, QString script_){
    QString error="";
    QTextStream ss(&error,QIODevice::ReadOnly);

    QScriptEngine* engine = vm->makeEngine();

    //Add Motors to Engine enviroment
    QString name="";
    QTextStream ns(&name,QIODevice::WriteOnly);
    QScriptValue motorArray = engine->newArray(vm->eInterface.getMotors().size());
    engine->globalObject().setProperty("motors",motorArray);
    foreach(Motor* m, vm->eInterface.getMotors()){
        name.clear();
        QScriptValue scriptmotor = engine->newQObject(m);
        ns<< ""<<m->getID();
        motorArray.setProperty(name,scriptmotor);
    }


    //Added Coordinated Motion object to engine
    JsCmotion jscm_;
    jscm_.setCmotion(vm->eInterface.getCoordinatedMotion());
    QScriptValue scriptCMotion = engine->newQObject(&jscm_);
    engine->globalObject().setProperty("cmotion",scriptCMotion);



    if (engine->checkSyntax(script_).state()==QScriptSyntaxCheckResult::Error){
       ss<<engine->checkSyntax(script_).errorMessage();
    }


    engine->evaluate(script_);

    if (engine->hasUncaughtException()) {
       ss<<engine->uncaughtException().toString();
    }
    return error;

}
