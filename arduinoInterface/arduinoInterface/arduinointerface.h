#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QObject>
#include "qextserialport.h"
#include <QVector>
#include <QStringList>

class ArduinoInterface : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoInterface(QObject *parent = 0);
    ArduinoInterface(QString port, BaudRateType baudrate, QObject *parent = 0);

    bool isReady();

signals:
    void portNotOpen();
    void queueLength(int i);
    void num_outstanding_cmds(int i);

public slots:
    bool connectPort(QString port, BaudRateType baudrate);
    void disconnect();
    void addToQueue(QStringList sl);
    void writeCommands(QStringList sl);
    void stopQueue();
    void startQueue();
    void clearQueue();

private slots:
    void _write(QString s);
    void _runQueue();
    void onDataAvailable();

private:
    QextSerialPort* port_;
    QVector< QString > queue_;
    int num_outstanding_cmds_;
    bool run_queue_;
};

#endif // ARDUINOINTERFACE_H
