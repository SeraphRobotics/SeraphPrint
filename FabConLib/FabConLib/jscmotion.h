#ifndef JSCMOTION_H
#define JSCMOTION_H

#include <QObject>
#include "coordinatedmotion.h"
#include <QtScript>
#include "jsnpath.h"


// used only for the runScipt function in virtualmachines
class JsCmotion : public QObject
{
Q_OBJECT
public:
    JsCmotion();
    void setCmotion(CoordinatedMotion* cmotion);

signals:

public slots:
    int getNumberOfAxes();

    void moveAlongPath(QScriptValue points);

public:
    bool hasCM;
private:
    CoordinatedMotion* cmotion_;

};

#endif // JSCMOTION_H
