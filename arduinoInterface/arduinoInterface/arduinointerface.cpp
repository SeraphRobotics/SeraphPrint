#include "arduinointerface.h"

#include <QDebug>

ArduinoInterface::ArduinoInterface(QObject *parent) :
    QObject(parent),num_outstanding_cmds_(0),run_queue_(false)
{
    port_ = new QextSerialPort();
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
}

ArduinoInterface::ArduinoInterface(QString port, BaudRateType baudrate, QObject *parent):
    QObject(parent),num_outstanding_cmds_(0),run_queue_(false)
{
    port_ = new QextSerialPort(port);//,QextSerialPort::Polling
    port_->setBaudRate( baudrate);
    port_->setFlowControl(FLOW_OFF);
    port_->setParity(PAR_NONE);
    port_->open(QIODevice::ReadWrite);
    //    port_->set
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
}

bool ArduinoInterface::isReady(){
    return port_->isOpen();
}


bool ArduinoInterface::connectPort(QString port, BaudRateType baudrate){
    if (port_->isOpen()){port_->close();}
    delete port_;
    port_ = new QextSerialPort(port);
    port_->setBaudRate(baudrate);
    port_->setFlowControl(FLOW_OFF);
    port_->setParity(PAR_NONE);
    port_->open(QIODevice::ReadWrite);
    qDebug()<<port_->isOpen();
    return port_->isOpen();
}
void ArduinoInterface::disconnect(){
    port_->close();
    qDebug()<<port_->isOpen();
}

void ArduinoInterface::addToQueue(QStringList sl){
    foreach(QString s,sl){
        queue_.append(s);
    }
}
void ArduinoInterface::writeCommands(QStringList sl){
    foreach(QString s,sl){
        _write(s);
    }
}

void ArduinoInterface::stopQueue(){
    run_queue_=false;
    queueLength(queue_.size());
}
void ArduinoInterface::startQueue(){
    run_queue_=true;
    queueLength(queue_.size());
}

void ArduinoInterface::clearQueue(){
    queue_.clear();
    queueLength(queue_.size());
}

void ArduinoInterface::_runQueue(){
    _write(queue_.first());
    queue_.pop_front();
}

void ArduinoInterface::_write(QString s){
    if (!isReady() ){return;}

    s=s.simplified();
    s=s.remove(' ');
    s=s.remove("\t");

    QByteArray ba = s.toStdString().c_str();
    port_->write(ba,ba.length());
    num_outstanding_cmds_++;
    qDebug()<<num_outstanding_cmds_;
    qDebug()<<ba.toHex();
    qDebug()<<s.toStdString().c_str();
    emit num_outstanding_cmds(num_outstanding_cmds_);
}

void ArduinoInterface::onDataAvailable(){
    QByteArray data = port_->readAll();
    qDebug()<<"received: "<<QString(data);
    QString c = QString(data);
    if("ok" == c){
        num_outstanding_cmds_--;
        emit num_outstanding_cmds(num_outstanding_cmds_);
        if(run_queue_){
            _runQueue();
        }
    }else{
        qDebug()<<c;
    }
}
