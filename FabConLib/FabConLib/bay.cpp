#include "bay.h"
#include <QTextStream>
#include <stdio.h>
#include "testing/util.h"

Bay::Bay():engine_(),location_(3,0.0){
    material_.id = 0;
}

Bay::Bay(const QDomNode& sourceDomNode):engine_() {
    material_.id = 0;
    QDomNodeList bayChildren = sourceDomNode.childNodes();
    for (unsigned int i=0; i<bayChildren.length();i++) {
        QDomNode bchild = bayChildren.at(i);
        if (bchild.isComment()) {continue;}

        if ("id" == bchild.nodeName().toLower()) {
            id_ = bchild.nodeValue().toInt();

        } else if ("volume"== bchild.nodeName().toLower()) {
            max_volume_ = bchild.nodeValue().toDouble();

        } else if ("location"==bchild.nodeName().toLower()) {
            QVector<double> loc(3,0);
            QDomNodeList locChildren = bchild.childNodes();
            for (unsigned int j = 0; j < locChildren.length(); j++) {

                QDomNode lchild = locChildren.at(j);
                if ("x"==lchild.nodeName()) {
                    loc[0] = lchild.nodeValue().toDouble();
                } else if ("y"==lchild.nodeName()) {
                    loc[1] = lchild.nodeValue().toDouble();
                } else if ("z"==lchild.nodeName()) {
                    loc[2] = lchild.nodeValue().toDouble();
                }
            location_ = loc;
            }
        } else if ("actuation"==bchild.nodeName().toLower()) {
            QDomNodeList aChildren = bchild.childNodes();
            QList<QString> actuatornames;
            for (unsigned int k = 0; k < aChildren.length(); k++) {
                QDomNode achild = aChildren.at(k);
                if (achild.isComment()) { continue; }
                if ("actuatorid" == achild.nodeName().toLower()) {
                    QString value = achild.toElement().text();
                    actuatornames.append(value);

                } else if ("script" ==achild.nodeName().toLower()) {
                    QDomNodeList scriptChildren = achild.childNodes();
                    for (unsigned int h = 0; h < scriptChildren.length(); h++) {
                        QDomNode schild = scriptChildren.at(h);
                        if (schild.isCDATASection()) {
                            script_=schild.toCDATASection().data();
                        }
                    }
                }else {
                    scriptSettings_[achild.nodeName()]=achild.toElement().text();
                }
            }
            actuatorNames_ = actuatornames;
        }
    }
}





void Bay::setId(int id) {
    id_ = id;
}

int Bay::getId() {
    return id_;
}

void Bay::setMaxVolume(double vol) {
    max_volume_ = vol;
}

double Bay::getMaxVolume() {
    return max_volume_;
}

void Bay::setLocation(QVector<double> location) {
    location_ = location;
}

QVector<double> Bay::getLocation() {
    return QVector<double>(location_);
}

void Bay::clearVolume() {
    volume_=0.0;
}

QString Bay::getErrors() {
    return error_;
}

//Materials
bool Bay::hasMaterial()const {
    return !(material_.id==0);
}

const Material Bay::getMaterial() const{
    return material_;
}

void Bay::setMaterial(Material material) {
    qDebug()<<"Set Material to "<< material.name;
    material_ = material;
    QScriptValue v = engine_->toScriptValue(material_);
    engine_->globalObject().setProperty("material",v);
}

void Bay::setEngine(QScriptEngine* engine) {
    engine_ = engine;
    QMapIterator<QString, QString> i(scriptSettings_);
    while (i.hasNext()) {
         i.next();
         QScriptValue scriptvalue(engine_,i.value());
         engine_->globalObject().setProperty(i.key(),scriptvalue);
     }

    QScriptValue actuatorlist = engine_->newArray(actuatorNames_.size());
    for(int j=0;j<actuatorNames_.length();j++) {
        actuatorlist.setProperty(j,QScriptValue(engine_,actuatorNames_.at(j) ) );
    }
    engine_->globalObject().setProperty("actuatorNames",actuatorlist);
    engine_->evaluate(script_);
    qScriptRegisterMetaType(engine_,objFromVoxel, voxelFromObj);
    qScriptRegisterMetaType(engine_,objFromPath, pathFromObj);
    qScriptRegisterMetaType(engine_,objFromMat, matFromObj);
}

//Actuation
QStringList Bay::onStartPath(){

    QTextStream ss(&error_,QIODevice::WriteOnly);
    QScriptValue pathfunction = engine_->globalObject().property("onStartPath");
    if(!pathfunction.isValid()) {
        ss<<"\n onStartPath: NOT VALID FUNCTION";
        QStringList returnlist;
        return returnlist;
    }
    QScriptValue jsStringList = pathfunction.call(QScriptValue(),QScriptValueList());
    return QStringListFromStringMatrix(jsStringList);
}
QStringList Bay::onEndPath(){
    QTextStream ss(&error_,QIODevice::WriteOnly);
    QScriptValue pathfunction = engine_->globalObject().property("onEndPath");
    if(!pathfunction.isValid()) {
        ss<<"\n onEndPath: NOT VALID FUNCTION";
        QStringList returnlist;
        return returnlist;
    }
    QScriptValue jsStringList = pathfunction.call(QScriptValue(),QScriptValueList());
    return QStringListFromStringMatrix(jsStringList);
}

QStringList Bay::onStartVoxel(){
    QTextStream ss(&error_,QIODevice::WriteOnly);
    QScriptValue pathfunction = engine_->globalObject().property("onStartVoxel");
    if(!pathfunction.isValid()) {
        ss<<"\n onStartVoxel: NOT VALID FUNCTION";
        QStringList returnlist;
        return returnlist;
    }
    QScriptValue jsStringList = pathfunction.call(QScriptValue(),QScriptValueList());
    return QStringListFromStringMatrix(jsStringList);
}

QStringList Bay::onEndVoxel(){
    QTextStream ss(&error_,QIODevice::WriteOnly);
    QScriptValue pathfunction = engine_->globalObject().property("onEndVoxel");
    if(!pathfunction.isValid()) {
        ss<<"\n onEndVoxel: NOT VALID FUNCTION";
        QStringList returnlist;
        return returnlist;
    }
    QScriptValue jsStringList = pathfunction.call(QScriptValue(),QScriptValueList());
    return QStringListFromStringMatrix(jsStringList);
}


QStringList Bay::onPath(XDFLPath path) {
    QStringList returnlist;
    QTextStream ss(&error_,QIODevice::WriteOnly);
    if(material_.id != path.materialID) {
        ss << "\n onPath: Improper path sent to bay, material did not match ID.";
        return returnlist;
    }

    QMap<QString,QString> properties = material_.property;

    double v = properties.value("pathwidth").toDouble()
             * properties.value("pathheight").toDouble()
             * properties.value("areaconstant").toDouble()
             * path.length();
    volume_+=v;
    qDebug()<<"Path volume is "<<v;

    QScriptValue pathfunction = engine_->globalObject().property("onPath");
    if(!pathfunction.isValid()) {ss<<"\n onPath: NOT VALID FUNCTION";}

    QScriptValue p = engine_->toScriptValue(path);
    QScriptValue jsStringList = pathfunction.call(QScriptValue(),QScriptValueList()<<p);

    ss<<"\nPath called ";
    if (engine_->hasUncaughtException()) {
        ss<<"\tERROR: %s"<<engine_->uncaughtException().toString();
        return returnlist;
    }

    returnlist+=onStartPath();
    returnlist+=QStringListFromStringMatrix(jsStringList);
    returnlist+=onEndPath();
    return returnlist;

}

QStringList Bay::onVoxel(XDFLVoxel voxel) {
    QStringList returnlist;
    volume_ += voxel.volume;
    QTextStream ss(&error_,QIODevice::ReadOnly);


    QScriptValue voxelfunction = engine_->globalObject().property("onVoxel");
    if(!voxelfunction.isValid()) {ss<<"\n onVoxel: NOT VALID FUNCTION";}
    QScriptValue v = engine_->toScriptValue(voxel);
    QScriptValue jsStringList = voxelfunction.call(QScriptValue(),QScriptValueList()<<v);
    ss<<"\nVoxel Returned ";
    if (engine_->hasUncaughtException()) {
        ss<<"\nERROR: %s"<<engine_->uncaughtException().toString();
        return returnlist;
    }

    returnlist+=onStartVoxel();
    returnlist+=QStringListFromStringMatrix(jsStringList);
    returnlist+=onEndVoxel();
    return returnlist;
}


QStringList Bay::jogActuators(double amount,double time){
    QStringList returnlist;
    QListIterator<QString> i(actuatorNames_);
    float d=0;
    while(i.hasNext()){
        returnlist.append("G92 "+i.next()+QString::number(0));
        d+=amount;
    }
    i.toFront();
    QString s="G1 ";
    while(i.hasNext()){
        s.append(" "+i.next()+QString::number(0));
    }
    s.append(" F"+QString::number(d/time));
    returnlist.append(s);

    return returnlist;
}

QStringList QStringListFromStringMatrix(const QScriptValue &obj) {
    QStringList slist;
    int len = obj.property("length").toInt32();
    for(int i=0;i<len;i++) {
        QScriptValue scriptvector = obj.property(i);
        slist.append(scriptvector.toString());
    }
    return slist;
}
