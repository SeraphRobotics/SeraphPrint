#ifndef INTERFACE_H
#define INTERFACE_H

#endif // INTERFACE_H

#include <iostream>
#include <QObject>
#include <QMap>
#include "FabAtHomePrinter.h"
#include "printthread.h"
#include "Motor.h"

using namespace std;
using namespace PROJECT_NAMESPACE;

class Interface : public QObject
{
    Q_OBJECT

private:

    /**
      Keeps track of the current stage of printing in order to handle for errors and make sure the user
      does not do anything out of order such as printing before initializing the printer.
     */
    enum PrintingStages {NOT_INITIALIZED, CONFIG_LOADED, MODEL_FILE_LOADED, PRINTING};
    bool isPaused;
    int currentStage;
    FabAtHomePrinter *printer;
    PrintThread *pThread;

public:

    struct FAH_POSITION
    {
        double x;
        double y;
        double z;
    };

    Interface();


    /**
	 Execute all paths which are currently loaded.
	 A call to this function returns when the print has finished.
	 If fabricationThread != NULL, messages will periodically be stored in displayText describing
	 what the printer is currently doing and progress will be reported to fabricationThread
	 when the message changes.
     */
    void print();


    /**
         Loads the configuration file and initializes the printer
	 @param file The path from the file dialog
	 @param port The port to load from	
	 @return "" iff successful or an error message.
     */

    bool loadConfigFile(QString file, QString port);

    /**
         Loads the configuration file and initializes the printer.
         This function is used to load in the port name automatically, and then call the loadConfigFile function
         with the port name argument.
         @param file The path from the file dialog
         @return "" iff successful or an error message.
     */
    bool loadConfigFile(QString file);

    /**
      Returns the current state the printer is in. Either "PRINTING," "IDLE," or "PAUSED"
      @return The state of the printer
     */
    QString getState();

    /**
      Load a file specifying material configurations and paths.
      @param filePath The name of the path of the file to load
      @return "" iff successful or an error message.
     */
    bool loadFabFile(QString filePath);

    /**
      @return The number of paths currently loaded.
     */
    int numLoadedPaths(void);

    /**
      @return The number of bays currently loaded.
     */
    int numLoadedBays(void);

    /**
      @return The current path during the print job.
      @todo Implement this
     */
    int currentPath();

    /**
      Moves the axes motors to a relative position specified by the user
      @param motor The motor to move
      @param x The x coordinate
      @param y The y coordinate
      @param z The z coordinate
      @return 1 if successful, 0 if not
     */
    bool move(double x, double y, double z);

    /**
      Moves the bay to an absolute position specified by the user
      @param motor The motor to move
      @param x The x coordinate
      @param y The y coordinate
      @param z The z coordinate
      @return true if successful, false if not
     */
    bool moveAbsolute(double x, double y, double z);

    /**
      Moves the bay motor to a relative position specified by the user
      @param bay The number of the bay motor to move
      @param distance The distance for the motor to travel
      @return true if successful, false if not
     */
    bool moveBayMotor(int bay, double distance);

    /**
      Moves the bay motor to an absolute position specified by the user
      @param bay The number of the bay motor to move
      @param distance The distance for the motor to travel
      @return true if successful, false if not
     */
    bool moveAbsoluteBayMotor(int bay, double distance);

    /**
	 Pause print after the current path finishes.
     */
    bool pausePrint();

    /**
         Resumes print after the printer is paused.
     */
    bool resumePrint();

    /**
      @param motor The string representation of the motor
      @return The velocity of the given motor, -1.0 if the string is invalid
     */
    double getVelocity(QString motor);

    /**
      @param motor The string representation of the motor
      @return The acceleration of the given motor, -1.0 if the string is invalid
     */
    double getAcceleration(QString motor);

    /**
      @param bay The integer representation of the bay (ranging from 0 to n-1 if there are n bays)
      @return The velocity of the given motor, -1.0 if the string is invalid
     */
    double getBayVelocity(int bay);

    /**
      @param bay The integer representation of the bay (ranging from 0 to n-1 if there are n bays)
      @return The acceleration of the given motor, -1.0 if the string is invalid
     */
    double getBayAcceleration(int bay);


    /**
          Sets the velocity of an axis motor
      @param strMotor A string representation of the motor ("X", "Y", or "Z")
      @return true if successful, false otherwise
     */
    bool setVelocity(QString strMotor, double velocity);

    /**
      Sets the acceleration of an axis motor
      @param strMotor A string representation of the motor ("X", "Y", or "Z")
      @return true if successful, false otherwise
     */
    bool setAcceleration(QString motor, double acceleration);

    /**
      Sets the acceleration for a bay motor
      @param bay The integer representation of the bay (ranging from 0 to n-1 if there are n bays)
      @return true if successful, false otherwise
     */
    bool setBayVelocity(int bay, double velocity);

    /**
      Sets the acceleration for a bay motor
      @param bay The integer representation of the bay (ranging from 0 to n-1 if there are n bays)
      @return true if successful, false otherwise
     */
    bool setBayAcceleration(int bay, double acceleration);

    /**
      Cancel print after the current path finishes.
      Requires: isPrinting()
     */
    bool cancelPrint();

    /**
      Redo the current path after the current path finishes.
      Requires: isPrinting()
     */
    bool redoPath();

    /**
      Force stops motors
     */
    bool stopMotors();

    /**
      Resets the positions of the motors
     */
    bool resetPos();

    /**
      @return The current X,Y,Z position of the motors
     */
    double getX();

    double getY();

    double getZ();

    /**
      Equips a certain bay with the specified material
      @param bay The integer representation of the bay (ranging from 0 to n-1 if there are n bays)
      @param material The material
      @return True if successful, false otherwise
     */
    bool equipMaterial(int bay, QString material);

    /**
      @param bay The integer representation of the bay (ranging from 0 to n-1 if there are n bays)
      @return The string representation of the material for the specified bay, otherwise returns an empty
      string if the integer repesentation for the bay is invalid
     */
    QString getMaterial(int bay);

    /**
      Removes the current configuration file and closes the port
     */
    bool removeConfig();


signals:

    /**
      A signal that takes in a string
     */
    void callWarning(QString);

private slots:

    //a slot that will be called when the print job is done through a signal/slot connection
    void donePrinting();

};
