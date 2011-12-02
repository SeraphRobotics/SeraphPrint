#ifndef XYZMOTION_H
#define XYZMOTION_H

#include <QObject>
#include <QMap>
#include "motor.h"
#include <QtScript>
#include "npath.h"
#include "nmotion.h"
#include "xdflpath.h"
#include <QDomNode>

struct axis{
    QString name;
    double range;
    double revPerDist;
    int actuatorID;
};


class XYZMotion: public QObject
{
Q_OBJECT
public:
    XYZMotion();
    XYZMotion(const QDomNode& sourceDomNode);

    //backup contructor settings
    void setAxes(QMap<QString,axis> axismap);

    void setAcceleration(double a);
    double getAcceleration()const;

    //for vm
    void setFrequency(int frequency);

    void setIdMap(QMap<int,int> map);

    // general usage
    NPath pathTo(double x, double y, double z, double speed);

    NPath pathAlong(XDFLPath path,double speed);

    State positionToState(double x,double y,double z);

    double distanceFromState(State* state);

private:

    void accelerateAlong(NPath* np, QList<Point> accel_list, double dist_a, bool deccel);

private:
    double acceleration_;
    QMap<QString,axis> axismap_;
    QMap<int,int> idToStateIndex_;
    int statesize_;
    int frequency_;

};



#endif // XYZMOTION_H
