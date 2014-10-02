#include "arduinointerface.h"

#include <QDebug>
#include <stdint.h>

ArduinoInterface::ArduinoInterface(QObject *parent) :
    QThread(parent),current_line(0), previous_line(""),run_queue_(false),receivedBuffer(""),start_received(false)
{
    port_ = new QextSerialPort();
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    readTimer = new QTimer();
    readTimer->setInterval(10);
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readCheck()));
    readTimer->start();
}

ArduinoInterface::ArduinoInterface(QString port, BaudRateType baudrate, QObject *parent):
    QThread(parent),current_line(0), previous_line(""),run_queue_(false),receivedBuffer(""),start_received(false)
{
    port_ = new QextSerialPort(port);//,QextSerialPort::Polling
    port_->setBaudRate( baudrate);
    port_->setFlowControl(FLOW_OFF);
    port_->setParity(PAR_NONE);
    port_->open(QIODevice::ReadWrite);
    //    port_->set
    qDebug()<<port_->isOpen();
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    readTimer = new QTimer();
    readTimer->setInterval(10);
    connect(readTimer,SIGNAL(timeout()),this,SLOT(readCheck()));
    readTimer->start();
    //_write( QString("M110") );
}
ArduinoInterface::~ArduinoInterface(){
    port_->close();
    delete port_;
}


int ArduinoInterface::queuesize(){
    return printqueue_.size();
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
    //_write( QString("M110") );
    qDebug()<<port_->isOpen();
    return port_->isOpen();
}
void ArduinoInterface::disconnect(){
    port_->close();
    qDebug()<<port_->isOpen();
}

void ArduinoInterface::addToQueue(QStringList sl){
    bool runstart = printqueue_.isEmpty();
    foreach(QString s,sl){
        printqueue_.append(s);
    }
    if(runstart){
        startQueue();
    }
    emit queuesize(printqueue_.size());
}
void ArduinoInterface::writeCommands(QStringList sl){
    if(run_queue_ ){//|| !start_received
        priorityqueue +=sl;
        qDebug()<<"queued"<<sl;
        qDebug()<<run_queue_;
        qDebug()<<start_received;
    }else{
        foreach(QString s, sl){
            _write(s);
        }
    }
}

void ArduinoInterface::stopQueue(){
    run_queue_=false;
}
void ArduinoInterface::startQueue(){
    if(printqueue_.isEmpty()){return;}
    run_queue_=true;
    _write(printqueue_.first());
    printqueue_.pop_front();
}

void ArduinoInterface::clearQueue(){
    printqueue_.clear();
    stopQueue();
    emit queuesize(printqueue_.size());
}

int ArduinoInterface::checksum(QString s){
    int cs = 0;
    int i = 0;
    if(s.size()>0){
        for(i = 0;i<s.size(); i++){
            if(s.at(i)=='*'){
                break;
            }
           cs = cs ^ s.at(i).toAscii();
        }
        cs &= 0xff;
    }
    return cs;
}
void ArduinoInterface::_write_next(){
    if(!priorityqueue.isEmpty()){
        _write(priorityqueue.takeFirst());
        qDebug()<<"***************running from priority********************\n";
    }else if(!printqueue_.isEmpty()){
        _write(printqueue_.takeFirst());
        emit queuesize(printqueue_.size());
    }
}


void ArduinoInterface::_write(QString s){
    if (!isReady() ){return;}

    previous_line = s;
    s=s.simplified();
//    s=s.remove(' ');
//    s=s.remove("\t");

    s = "N" + QString::number(++current_line)+" "+s;

#ifdef DEBUGGING
    //qDebug()<<s;
#endif


    //qDebug()<<"Cs: "<<cs;

    s+="*"+QString::number(checksum(s))+"\n";
    qDebug()<<"writing:"<<s;
    QByteArray ba = s.toStdString().c_str();
    port_->write(ba,ba.length());


}

void ArduinoInterface::readCheck(){
//    qDebug()<<"checked, found "<<port_->bytesAvailable();
    if(port_->bytesAvailable()>0){
        onDataAvailable();
    }

}


void ArduinoInterface::onDataAvailable(){
    QByteArray data = port_->readAll();
    QString c = QString(data).toLower();
    c = receivedBuffer+c;
    c=c.simplified();
    c=c.remove("\n");
//    c=c.remove(' ');
//    c=c.remove("\t");
    c = QString(data).toLower();
    qDebug()<<c;

//    c=c.simplified();
//    c=c.remove(' ');
//    c=c.remove("\t");
//    return;
    if (c.contains("start")){
//        current_line+=20;
        start_received = true;
        _write("M110 ");
//        run_queue_=true;
        receivedBuffer.clear();
    }else if ( c.contains("resend") || c.contains("checksum") || c.contains("error")){
        --current_line;
        _write(previous_line);
        receivedBuffer.clear();
    }else if(c.contains("ok") || c.contains("wait")){
        _write_next();
        qDebug()<<c;
//        if(printqueue_.size()>0){ //run_queue_ &&
//            _write(printqueue_.takeFirst());

//        }
        receivedBuffer.clear();
    }else {
        receivedBuffer.append(c);
//        qDebug()<<c;
    }
}
