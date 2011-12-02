#ifndef JSXYZ_H
#define JSXYZ_H

#include <QObject>
#include <QtScript>
#include "xyzmotion.h"

class JsXYZ : public QObject
{
Q_OBJECT
public:
    JsXYZ();

    void setXYZ(XYZMotion* xyz);

public slots:

//    QScriptValue pathTo(QScriptContext * context,QScriptEngine *engine);
    QScriptValue pathTo(QScriptValue x,QScriptValue y,QScriptValue z, QScriptValue speed);

    QScriptValue pathAlong(QScriptValue JSPath,QScriptValue JSspeed);
//    QScriptValue pathAlong(QScriptContext * context,QScriptEngine *engine);

private:
    XYZMotion* xyz_;
};

#endif // JSXYZ_H
