#ifndef COORDINATEDMOTION_H
#define COORDINATEDMOTION_H

#include <QObject>
#include "motor.h"


#include "npath.h"
#include "nmotion.h"
#include <QMap>



class CoordinatedMotion : public QObject
{
    Q_OBJECT
public:
    CoordinatedMotion();
    CoordinatedMotion(QMap<int,Motor*> motors);
    bool moveAlongPath(NPath points);

    bool moveAlongPath(NPath points, int startPointIndex);

    void setMotors(QMap<int,Motor*> motors);

    void setGroupAddress(byte address);

    void setFrequency(int frequency);

    int getFrequency();

    bool initializePathMode();


    /**
     * @returns true if the NPath is valid for the motor configuration
     * Uses the NPath in relative coordinates
     **/
    bool validateNPath(NPath path);

    QMap<int,int> getIdToStateIndexMap();

public slots:

    int getNumberOfAxes();

    QString getErrors();


private:
    QMap<int,Motor*> motors_; // the integer id of the state variable and the corresponding motor instance
    bool initialized_;
    byte X_Y_Z_GROUP_ADDRESS;
    QString error_string;
    bool pathbegan_;
    QMap<int,double> scales;
    QMap<int,int> addressMap;
    int frequency_;

};

#endif // COORDINATEDMOTION_H
