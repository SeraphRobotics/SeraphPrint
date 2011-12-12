#ifndef JSCI_H
#define JSCI_H

#include <QObject>
#include <QVariant>
#include "../coreinterface.h"

class JsCiTest : public QObject
{
    Q_OBJECT
public:
    JsCiTest();
    QString loadXDFL();
    void runScript();

signals:

public slots:
    void test();
    void connected(int i);


private:
    CoreInterface *ci_;
    QScriptEngine engine_;
    QString script_;

};

#endif // JSCI_H
