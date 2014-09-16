#include "UV.h"
#include <QDebug>
#include <math.h>

UV::UV() :
    connected(false)
{
}
UV::UV( const QDomNode& sourceDomNode ) :
    connected(false)
{
    QString port;
    QDomNodeList bayChildren = sourceDomNode.childNodes();
    qDebug()<<"num UV children:"<< bayChildren.length();
    for(uint i=0; i<bayChildren.length();i++){
        QDomNode bchild = bayChildren.at(i);
        if (bchild.isComment()) {continue;}
        if ("comport" == bchild.nodeName().toLower()) {
            port = bchild.toElement().text().replace("\"","");
             qDebug()<<"port: "<<port;
        }
    }
    setComPort(port);
}




void UV::setComPort(QString port){
    comport_= new QextSerialPort(port);
    comport_->setBaudRate(BAUD9600);
    comport_->setFlowControl(FLOW_OFF);
    comport_->setParity(PAR_NONE);
    connected = comport_->open(QIODevice::ReadWrite);

    connect(comport_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));

    if (!connected){
        qDebug()<<"The head could not connect to "<<port;
    }else{
        qDebug()<<"Connected";

    }
}



void UV::setValue(int PWM){
    if(!comport_->isOpen()){
        connected=false;
        qDebug()<<"comport not open";
        return;
    }

    QChar c(PWM);

    char fill= c.cell();
    QByteArray ba(1,fill);
    ba.push_front(c.row());

    qint64 l = ba.length();
    qDebug()<<"writing"<<ba.toHex();
    comport_->write(ba,l);
}

void UV::onDataAvailable(){
    QByteArray data = comport_->readAll();
    qDebug()<<"received: "<<QString(data);
}

