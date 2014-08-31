#ifndef UV_H
#define UV_H

#include <QObject>
#include "../../JrkerrElectronics/Windows/qextserial/qextserialport.h"
#include <QDomNode>

class UV : public QObject
{
    Q_OBJECT
public:
    explicit UV();
    UV(const QDomNode& sourceDomNode);

public slots:
    void setComPort(QString port);
    void setValue(int PWM);//QScriptValue PWM value
    void onDataAvailable();

public:
    bool connected;
private:
    QextSerialPort* comport_;
};

#endif // UV_H
