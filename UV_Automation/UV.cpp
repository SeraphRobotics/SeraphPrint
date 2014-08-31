#include "UV.h"
#include <QDebug>
#include <math.h>


UV::UV() :
    connected(false)
{
}

void UV::setComPort(QString port){
    comport_= new QextSerialPort(port);
    comport_->setBaudRate(BAUD9600);
    comport_->setFlowControl(FLOW_OFF);
    comport_->setParity(PAR_NONE);
    connected = comport_->open(QIODevice::ReadWrite);

    connect(comport_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));

    if (!connected){
        qDebug()<<"The head could not connect";
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

//    qDebug()<<QString::number(PWM,16);
//    char fill = QString::number(255,16).toStdString()[0];
    QChar c(PWM);

    char fill= c.cell();
    QByteArray ba(1,fill);

//    QString sa = QString::number(PWM,16);
//    QByteArray ba(sa.toUtf8());
//    qDebug()<<"OUtputing: "<<PWM%255<<" : size"<<ba.length();
    qint64 l = ba.length();
//    qDebug()<<
    comport_->write(ba,l);
}

void UV::onDataAvailable(){
//    QByteArray data = comport_->readAll();
//    qDebug()<<"received: "<<QString(data);
}

