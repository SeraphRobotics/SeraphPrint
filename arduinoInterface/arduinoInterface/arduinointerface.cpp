#include "arduinointerface.h"

#include <QDebug>

ArduinoInterface::ArduinoInterface(QObject *parent) :
    QObject(parent),num_outstanding_cmds_(0),run_queue_(false),current_line(100)
{
    port_ = new QextSerialPort();
    timer_ = new QTimer();
    timer_->setInterval(100);
    connect(timer_,SIGNAL(timeout()),this,SLOT(_runQueue()));
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));

}

ArduinoInterface::ArduinoInterface(QString port, BaudRateType baudrate, QObject *parent):
    QObject(parent),num_outstanding_cmds_(0),run_queue_(false),current_line(100)
{
    port_ = new QextSerialPort(port);//,QextSerialPort::Polling
    port_->setBaudRate( baudrate);
    port_->setFlowControl(FLOW_OFF);
    port_->setParity(PAR_NONE);
    port_->open(QIODevice::ReadWrite);
    //    port_->set
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    _write( QString("M110 ")+QString::number(current_line) );
    timer_ = new QTimer();
    timer_->setInterval(50);
    connect(timer_,SIGNAL(timeout()),this,SLOT(_runQueue()));
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
    _write( QString("M110 ")+QString::number(current_line) );
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
    timer_->stop();
    queueLength(queue_.size());
}
void ArduinoInterface::startQueue(){
    run_queue_=true;
    queueLength(queue_.size());
    timer_->start();
}

void ArduinoInterface::clearQueue(){
    queue_.clear();
    queueLength(queue_.size());
}

void ArduinoInterface::_runQueue(){
    if(queue_.size()>0){

#ifdef DEBUGGING
    qDebug()<<queue_.first();
#endif
    _write(queue_.first());
    queue_.pop_front();
    }else{
        timer_->stop();
    }

}

void ArduinoInterface::_write(QString s){
    if (!isReady() ){return;}


    s=s.simplified();
    s=s.remove(' ');
    s=s.remove("\t");

    if(num_outstanding_cmds_>10){
        queue_.append(s);
        startQueue();
    }else{
#ifdef DEBUGGING
    qDebug()<<s;
#endif
    QByteArray ba = s.toStdString().c_str();
    port_->write(ba,ba.length());
    num_outstanding_cmds_++;
    qDebug()<<num_outstanding_cmds_;
    //qDebug()<<ba.toHex();
    //qDebug()<<s.toStdString().c_str();
    emit num_outstanding_cmds(num_outstanding_cmds_);
    }
}

void ArduinoInterface::onDataAvailable(){
    QByteArray data = port_->readAll();
#ifdef DEBUGGING
    qDebug()<<"received: "<<QString(data);
#endif

    QString c = QString(data).toLower();
    c=c.simplified();
    c=c.remove(' ');
    c=c.remove("\t");

    if("ok" == c){
        num_outstanding_cmds_--;
        emit num_outstanding_cmds(num_outstanding_cmds_);
        if(run_queue_){
            _runQueue();
        }
    }else if ("start"){

    }else if ("resend"){
        --current_line;
        _runQueue();
    }else{
        qDebug()<<c;
    }
}
