#ifndef FABATHOMEPRINTER_H
#define FABATHOMEPRINTER_H

#include "Axis.h"
#include "Model.h"
#include "Motor.h"
#include "MaterialCalibration.h"
#include "InterpreterPath.h"
#include "Tool.h"
//PIC-SERVO path header files
#include "path.h"
#include "qdebug.h"
#include <QSemaphore>


/**
  This class contains all of the functions that are related to printing.
  Almost every function that does not include moving the individual motors starts in this class.
  */
namespace PROJECT_NAMESPACE
{
class FabAtHomePrinter : public QObject
{
    Q_OBJECT

    //CONSTANTS///////////////////////////////////////////////////////////////////////////////////////////
private:
    byte X_Y_Z_GROUP_ADDRESS;
    unsigned int NUM_MODULES, BAUD_RATE;
    unsigned int COM_PORT;
    double PLATFORM_DELTA;
    double PRINT_ACCELERATION;
    //The acceleration that is used while printing.  The unit of PRINT_ACCELERATION is U/(second^2).

    double OLD_MSPS;
    //Magic constant from line 58 of FabAtHomeParameters.h in model 1 code.
    //Used to calculate values for pushout and suckback.

    QSemaphore pauseSemaphore;
    //A QSemaphore that is triggered once the current path has ended and the pause button was pressed

private:
    Model model; //The model that represents everything from the fab file
    map<string, Motor, LessThanString> motors; //A map from motor names to motors.

    map<string, MaterialCalibration, LessThanString> materialCalibrations;
    //A map from material calibration names to material calibrations.

    bool pausePrintFlag, cancelPrintFlag, redoPathFlag, printing, initialized, paused;
    //flags that are triggered during print time if their respective buttons are clicked on

    /**
      Load the configuration file from the
      @param filePath The path from the file dialog
      @return "" iff successful or an error message.
     */
    string loadConfigFile(string filePath);

    /**
      Switch printer to path mode.
      @return true iff successful.
     */
    bool initializePathMode(void);

    /**
      Execute the path.
      The bay will execute pushout, standard flow, and suckback iff flowDuringPath is true.
      A call to this function returns when movement has finished.
      @param path The current path
      @param bay The bay
     */
    void executePath(const Path& path, Bay* bay, const bool flowDuringPath);

    /**
      Execute the points.
      The bay will execute pushout, standard flow, and suckback iff flowDuringPath is true.
      A call to this function returns when all points are in the path point buffer.
      @param points The list of points in the path
      @param bay The current bay for depositing material
      @param flowDuringPath Whether or not to deposit material for the path
      @param pushoutDistance Distance of initial push out
      @param pushoutVelocity Speed of initial push out
      @param standardDistance Distance of depositing material
      @param standardVelocity Speed of depositing material
      @param suckbackDistance Distance of suckback (occurs after material deposition)
      @param suckbackVelocity Speed of suckback (occurs after material deposition)
      @param suckbackPoint Point of which material deposition stops and suckback occurs
     */
    void executePoints(const vector<Point>& points,
                       Bay* bay,
                       const bool flowDuringPath,
                       double pushoutDistance,
                       double pushoutVelocity,
                       double standardDistance,
                       double standardVelocity,
                       double suckbackDistance,
                       double suckbackVelocity,
                       const Point& suckbackPoint);

    /**
      Move all points from segment list to path point buffer.
      Physical movement begins as soon as a point is in the path point buffer.
      The bay will execute pushout, standard flow, and suckback iff flowDuringPath is true.
      @param bay The current bay for depositing material
      @param startFlow Whether or not to start depositing material
      @param startSuckback Whether or not to start suckback of material
      @param pushoutDistance Distance of initial push out
      @param pushoutVelocity Speed of initial push out
      @param standardDistance Distance of depositing material
      @param standardVelocity Speed of depositing material
      @param suckbackDistance Distance of suckback (occurs after material deposition)
      @param suckbackVelocity Speed of suckback (occurs after material deposition)
      @param suckbackPoint Point of which material deposition stops and suckback occurs
     */
    void downloadSegmentList(Bay* bay,
                             bool startFlow,
                             bool startSuckback,
                             double pushoutDistance,
                             double pushoutVelocity,
                             double standardDistance,
                             double standardVelocity,
                             double suckbackDistance,
                             double suckbackVelocity,
                             const Point& suckbackPoint);

    /**
      Clears the segment list and then tries to add points into the segment list starting from startIndex.
      Segment list has size 1000 but this function does not necessarily fill it completely.
      @param points A list of points in the path
      @param startIndex The index of which to start adding points to the path buffer
      @return The last index of points that was added to the segment list or -1 if points is empty.
     */
    int fillSegmentList(const vector<Point>& points, const int startIndex);

    /**
      Locates the first bay with a specific material calibration
      @param The material calibration to look for
      @return A bay that has the material calibration loaded or NULL if no such bay exists.
     */
    Bay* findBay(MaterialCalibration*);

    /**
      Executes the path to pause during a print job
      @param The current location of the tool head
     */
    void executePausePath(const Point&);

    /**
      Executes the path
     */
    void executeSetupPath(const Point&, const Point&, const double&);

    /**
      Loads in the material calibration from the Fab file
      @param An object representing the place in the file where the material calibration settings are located
     */
    void loadMaterialCalibration(TiXmlNode*);
    string loadPath(TiXmlNode*);

    /**
      The copy constructor.  Private to prevent printer from being copied.
     */
    FabAtHomePrinter(const FabAtHomePrinter&);

    /**
      The copy assignment operator.  Private to prevent printer from being copied.
     */
    FabAtHomePrinter& operator=(const FabAtHomePrinter&);

    string displayText; //The text to display by the progress bar during a print job

public:
    QVector<string> bayMaterials;
    map<string, Axis, LessThanString> axes; //A map from axis names to axes.
    Tool tool; //An object that contains all the bay objects

    FabAtHomePrinter(void);

    /**
      Inserts into result the names of all material calibrations that are currently loaded.
      @param result The list of mate
     */
    void loadedMaterialCalibrations(vector<string>& result);

    /**
      @return The number of paths currently loaded.
     */
    int numLoadedPaths(void);

    /**
      @return The number of bays currently loaded.
     */
    int numLoadedBays(void);

    /**
      @return True iff printer is printing.
     */
    bool isPrinting(void);

    /**
      @return True iff printer is paused.
     */
    bool isPaused(void);

    /**
      Load a file specifying material configurations and paths.
      @param filePath The name of the path of the file to load
      @return "" iff successful or an error message.
     */
    string loadFabFile(string filePath);

    /**
      Returns the current state the printer is in out of "PRINTING," "IDLE," and "PAUSED"
      @return The state of the printer
     */
    string state();

    /**
      Initialize the printer.
      @return "" if successful or an error message if failed.
     */
    string initialize(const string& configFilePath, string portLocation);

    /**
      Equip a bay with a material calibration or unequip the bay if the material calibration is "".
      Requires that the printer is not printing and paused, and the bay and material calibration have been loaded.
     */
    void equipBay(const string& bayName, const string& materialCalibrationName);

    /**
      Execute all paths which are currently loaded.
      A call to this function returns when the print has finished.
      If fabricationThread != NULL, messages will periodically be stored in displayText describing
      what the printer is currently doing and progress will be reported to fabricationThread
      when the message changes.
     */
    void print();

    /**
      Perform clean up when done using printer.
      @return True iff successful.
     */
    bool cleanUp(void);

    /**
      Performs a "hard reset" with the current motors under the XYZ group address
     */
    void reset();

    /**
      Checks to see if the current printer configuration is initialized with a valid configuration
      @return true if initialized, false otherwise
     */
    bool isInitialized();

    void moveMotor(string str_motor);

    bool contains(string str_motor);

    bool containsMaterial(string cur_material);

    void moveMotor(string str_motor, double distance);

    //The destructor.
     ~FabAtHomePrinter(void);

public slots:

    /**
      Pause print after the current path finishes.
      Requires: isPrinting()
     */
    void pausePrint(void);

    /**
      Resumes print after a pause.
      Requires: isPrinting()
     */
    void resumePrint();

    /**
      Cancel print after the current path finishes.
      Requires: isPrinting()
     */
    void cancelPrint(void);

    /**
      Redo the current path after the current path finishes.
      Requires: isPrinting()
     */
    void redoPath(void);

    /**
      Force stops motors
      @todo Fix this function such that the program does not crash
     */
    void stopMotors();

    /**
      Resets the positions of the motors
     */
    void resetPos();

signals:

    /**
      A signal that is issued throughout the print job to update the status of the printer
      @param i The current path
      @param str The current status of the printer to be printed to the screen
     */
    void reportProgress(int i, QString str);

    /**
      Triggers a signal to call a message box to the screen
      @param str The text to be displayed in the message box
     */
    void callWarning(QString str);

    /**
      Issues a signal to mainwindow.cpp when done printing
     */
    void finishedPrinting();

};
}
#endif //ndef FABATHOMEPRINTER_H
