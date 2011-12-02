#ifndef XDFLVOXEL_H
#define XDFLVOXEL_H
#include <QtScript>
#include <QDomNode>

struct XDFLVoxel{
    int id;
    double volume;
    double x;
    double y;
    double z;
};
Q_DECLARE_METATYPE(XDFLVoxel)

XDFLVoxel voxFromQDom(QDomNode node);

QScriptValue objFromVoxel(QScriptEngine *engine, const XDFLVoxel &voxel);

void voxelFromObj(const QScriptValue &obj, XDFLVoxel &voxel);




#endif // XDFLVOXEL_H
