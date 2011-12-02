#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QMap>
#include <QDomNode>
#include <QtScript>


struct Material{
    int id;
    QString name;
    double Q;// Flow rate in mm^3/min
    QMap<QString,QString> property;
};

Q_DECLARE_METATYPE(Material)

Material materialFromDom(QDomNode node);

QScriptValue objFromMat(QScriptEngine *engine, const Material &mat);

void matFromObj(const QScriptValue &obj, Material &mat);

#endif // MATERIAL_H
