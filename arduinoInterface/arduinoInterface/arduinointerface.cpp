#include "arduinointerface.h"

#include <QDebug>
#include <stdint.h>

ArduinoInterface::ArduinoInterface(QObject *parent) :
    QObject(parent),current_line(0), previous_line(""),run_queue_(false)
{
    port_ = new QextSerialPort();
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));

}

ArduinoInterface::ArduinoInterface(QString port, BaudRateType baudrate, QObject *parent):
    QObject(parent),current_line(0), previous_line(""),run_queue_(false)
{
    port_ = new QextSerialPort(port);//,QextSerialPort::Polling
    port_->setBaudRate( baudrate);
    port_->setFlowControl(FLOW_OFF);
    port_->setParity(PAR_NONE);
    port_->open(QIODevice::ReadWrite);
    //    port_->set
    qDebug()<<port_->isOpen();
    connect(port_, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    //_write( QString("M110") );
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
    foreach(QString s,sl){
        queue_.append(s);
    }
    startQueue();
}
void ArduinoInterface::writeCommands(QStringList sl){
    foreach(QString s,sl){
        queue_.prepend(s);
    }
//    startQueue();
}

void ArduinoInterface::stopQueue(){
    run_queue_=false;
}
void ArduinoInterface::startQueue(){
    if(queue_.isEmpty()){return;}
    run_queue_=true;
    _write(queue_.first());
    queue_.pop_front();
}

void ArduinoInterface::clearQueue(){
    queue_.clear();
    stopQueue();
}

void ArduinoInterface::_write(QString s){
    if (!isReady() ){return;}

    previous_line = s;
    s=s.simplified();
//    s=s.remove(' ');
//    s=s.remove("\t");

    s = "N" + QString::number(++current_line)+" "+s;

#ifdef DEBUGGING
    qDebug()<<s;
#endif

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
    qDebug()<<"Cs: "<<cs;

    s+="*"+QString::number(cs)+"\n";
    qDebug()<<s;
    QByteArray ba = s.toStdString().c_str();
    port_->write(ba,ba.length());


}

void ArduinoInterface::onDataAvailable(){
    QByteArray data = port_->readAll();
    QString c = QString(data).toLower();
    c=c.simplified();
//    c=c.remove(' ');
//    c=c.remove("\t");
    c = QString(data).toLower();

#ifdef DEBUGGING
    qDebug()<<"received: "<<c;
#endif


//    c=c.simplified();
//    c=c.remove(' ');
//    c=c.remove("\t");
//    return;
    if (c.contains("start")){
//        current_line+=20;
        _write("M110 ");
        run_queue_=true;
    }else if ( c.contains("resend") || c.contains("checksum" || c.contains("error"))){
        --current_line;
        _write(previous_line);
    }else if(c.contains("ok")){
        if(run_queue_ && queue_.size()>0){
            _write(queue_.first());
            queue_.pop_front();
        }
    }else {
//        qDebug()<<c;
    }
}
