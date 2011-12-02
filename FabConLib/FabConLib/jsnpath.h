#ifndef JSNPATH_H
#define JSNPATH_H

#include <QtScript>
#include "npath.h"




//QScriptValue NPath_ctor(QScriptContext *context,QScriptEngine *engine);

void npathFromMatrix(const QScriptValue &obj,NPath &npath);

QScriptValue matrixFromNPath(QScriptEngine *engine,NPath &npath);

QScriptValue matrixFromNPath(QScriptEngine *engine,NPath &npath, QVector<double> distances);

Q_DECLARE_METATYPE(NPath)

QScriptValue newJsState(QScriptContext *context, QScriptEngine *engine);

QScriptValue addState(QScriptContext * context,QScriptEngine *engine);

QScriptValue newJsNPath(QScriptContext *context, QScriptEngine *engine);

#endif // JSNPATH_H
