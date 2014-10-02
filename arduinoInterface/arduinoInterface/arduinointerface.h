#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QObject>
#include "qextserialport.h"
#include <QVector>
#include <QStringList>
#include <QTimer>

class ArduinoInterface : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoInterface(QObject *parent = 0);
    ArduinoInterface(QString port, BaudRateType baudrate, QObject *parent = 0);
    ~ArduinoInterface();

    bool isReady();

signals:
    void portNotOpen();

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
    void onDataAvailable();

private:
    int checksum(QString s);

private:
    QextSerialPort* port_;
    QStringList printqueue_;
    QStringList priorityqueue;
    int current_line;
    QString previous_line;
    bool run_queue_;
    QString receivedBuffer;
};

#endif // ARDUINOINTERFACE_H
