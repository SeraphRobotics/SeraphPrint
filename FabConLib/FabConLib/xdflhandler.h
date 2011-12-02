#ifndef XDFLHANDLER_H
#define XDFLHANDLER_H

#include <QObject>
#include <QDomNode>
#include "virtualmachines.h"
#include "xdflpath.h"
#include "xdflvoxel.h"
#include "material.h"
#include <QVector>

class XDFLHandler : public QThread
{
    Q_OBJECT
public:
     //explicit XDFLHandler(QObject *parent = 0);
    XDFLHandler();
    void run();
    int getNumCommands();

signals:
    void needMaterialChange(int id);// signals integer of the material ID that needs to be loaded

public slots:
    void loadFromDom(QDomDocument node);
    void setVM(VMPrototype* vm);
    QList<Material> getMaterials();
    void pause(bool paused);
    void resume();
    void pause();
    bool runXDFL();
    bool runXDFL(QDomNode command);

private:
    // for XDFL functions
    NPath dwell(double time_in_ms);
    void runNPath(NPath n);
    void setMaterial(int id);


public:
     QMap<int,Material> mat_map;

private:
    QDomNode xdfldom_;
    QDomNode commands_;
    VMPrototype *vm_;
    bool pause_;
    QMap<int,Bay*> material_bay_mapping_;
    State laststate_;
    int current_material_;
    int current_command_;


};

#endif // XDFLHANDLER_H
