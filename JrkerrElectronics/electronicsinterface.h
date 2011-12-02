#ifndef ELECTRONICSINTERFACE_H
#define ELECTRONICSINTERFACE_H

#include <QObject>
#include <QDomNode>

#include "nmccom.h"
#include "motor.h"
#include "coordinatedmotion.h"


class ElectronicsInterface : public QObject
{
    Q_OBJECT

public:
    ElectronicsInterface();

    /**
     * Builds the motors and coordinateMotion objects using the QDomNode information
     */
    QString initialize(QDomNode node, QString portLocation);

    /**
     * returns true if the system is initialized
     */
    bool isInitialized();

    /**
     * resets the electronics
     */
    void reset();

    /**
     * returns a pointer to the coordinatedmotion object
     * use isInitialized to ensure the object is built.
     */
    CoordinatedMotion* getCoordinatedMotion();

    /**
     * returns a list of the points to the motors.
     * use isInitialized to ensure the objects have been built
     */
    QList<Motor*> getMotors();

    /**
     * returns the motor wiht the id specified.
     */
    Motor* getMotor(int id);

    /**
     * waits the program until all motors finish moving.
     */
    void waitOnMove();

    QString getErrors();

private:

    void createCoodinatedMotion();

    void createMotor(QDomNode node);

    QString loadSettings(QDomNode node);

    bool cleanUp();

public:
    QList<Motor*> motors_;
private:
    CoordinatedMotion cmotion_;
    bool initialized_;

    unsigned int NUM_MODULES, BAUD_RATE;
    byte X_Y_Z_GROUP_ADDRESS;//JRKERR SPECIFIC
    QString COM_PORT;
    QString error_string_;
    int frequency_;
};

#endif // ELECTRONICSINTERFACE_H
