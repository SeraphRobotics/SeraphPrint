#include "FabAtHomePrinter.h"
#include <QMap>

FabAtHomePrinter::FabAtHomePrinter():
        pausePrintFlag(false),
        cancelPrintFlag(false),
        redoPathFlag(false),
        initialized(false),
        printing(false),
        paused(false),
        pauseSemaphore(0),
        displayText((string)"")
{
}

string FabAtHomePrinter::initialize(const string& filePath, string portLocation)
{
    if(!initialized)
    {
        string result = loadConfigFile(filePath);
        if(result.compare("") != 0)
        {
            return result;
        }

        //Connect to printer.
        stringstream ss;

        ss << portLocation;
        unsigned int numModulesFound = NmcInit(const_cast<char*>(ss.str().c_str()), BAUD_RATE);
        if(numModulesFound < NUM_MODULES)
        {
            ss.str("");
            ss << "Found " << numModulesFound << " modules but need " << NUM_MODULES << " modules.";
            return ss.str();
        }

        //Initialize all motors.
        for(map<string,Motor,LessThanString>::iterator i = motors.begin(); i != motors.end(); ++i)
        {
            string result = i->second.initialize();
            Util::assertTrue(result.compare("") == 0,result,__LINE__,__FILE__);
        }


        initialized = true;
    }
    return "";
}

void FabAtHomePrinter::pausePrint()
{
    pausePrintFlag = true;
}

void FabAtHomePrinter::resumePrint()
{
    pauseSemaphore.release();
}

void FabAtHomePrinter::cancelPrint()
{
    cancelPrintFlag = true;
}

void FabAtHomePrinter::redoPath()
{
    redoPathFlag = true;
}

void FabAtHomePrinter::equipBay(const string& bayName, const string& materialCalibrationName)
{
    Util::assertTrue(tool.bays.find(bayName) != tool.bays.end(),
                     "Trying to equip "+bayName+" with "+materialCalibrationName
                     +" but bay has not been loaded.",
                     __LINE__,
                     __FILE__);
    Util::assertTrue(materialCalibrationName.compare("") == 0
                     || materialCalibrations.find(materialCalibrationName) != materialCalibrations.end(),
                     "Trying to equip "+bayName+" with "+materialCalibrationName
                     +" but material calibration has not been loaded.",
                     __LINE__,
                     __FILE__);
    Util::assertTrue(!isPrinting() || isPaused(),"Cannot equip bay at this time.",__LINE__,__FILE__);
    MaterialCalibration* materialCalibration = materialCalibrationName.compare("") == 0 ?
                                               NULL :
                                               &(materialCalibrations.find(materialCalibrationName)->second);
    tool.bays.find(bayName)->second.materialCalibration = materialCalibration;
}

int FabAtHomePrinter::numLoadedPaths()
{
    return model.paths.size();
}

int FabAtHomePrinter::numLoadedBays()
{
    return tool.bays.size();
}

bool FabAtHomePrinter::initializePathMode()
{
    SetTangentTolerance(180.0f); //180.0f allows all angles.
    SetOrigin(0.0f, 0.0f, 0.0f);

    //aReset position of all motors.
    for(map<string,Motor,LessThanString>::iterator i = motors.begin(); i != motors.end(); ++i)
    {
        i->second.resetPosition();
    }
    return
            axes["X"].motor->setGroup(X_Y_Z_GROUP_ADDRESS, true)
            && axes["Y"].motor->setGroup(X_Y_Z_GROUP_ADDRESS, false)
            && axes["Z"].motor->setGroup(X_Y_Z_GROUP_ADDRESS, false)
            && SetPathParams2
            (
                    P_30HZ, //path frequency
                    10,
                    //Max number of points in the path point buffer at one time.  Max value is 87.
                    //A higher value results in longer downloads to the path point buffer.

                    axes["X"].motor->getAddress(),
                    axes["Y"].motor->getAddress(),
                    axes["Z"].motor->getAddress(),
                    X_Y_Z_GROUP_ADDRESS,
                    axes["X"].motor->getAddress(), //group leader
                    (float)axes["X"].motor->getCountsPerU(),
                    (float)axes["Y"].motor->getCountsPerU(),
                    (float)axes["Z"].motor->getCountsPerU(),
                    (float)PRINT_ACCELERATION
                    ) == 0;
}

string FabAtHomePrinter::loadConfigFile(string filePath)
{
    //Clear previously loaded data.
    axes.clear();
    motors.clear();
    tool.bays.clear();

    XMLParser parser;
    string result = parser.load(filePath);
    if(result.compare("") != 0)
    {
        return result;
    }

    //Load constants.
    COM_PORT = Util::assertType<unsigned int>(parser.text("fabAtHomePrinter 0\\electronics 0\\comPort 0"));
    NUM_MODULES = Util::assertType<unsigned int>(parser.text("fabAtHomePrinter 0\\electronics 0\\numModules 0"));
    BAUD_RATE = Util::assertType<unsigned int>(parser.text("fabAtHomePrinter 0\\electronics 0\\baudRate 0"));
    X_Y_Z_GROUP_ADDRESS = (byte)Util::assertType<unsigned int>
                          (parser.text("fabAtHomePrinter 0\\electronics 0\\xyzGroupAddress 0"));
    PLATFORM_DELTA = Util::assertType<double>(parser.text("fabAtHomePrinter 0\\motion 0\\platformDelta 0"));
    OLD_MSPS = Util::assertType<double>(parser.text("fabAtHomePrinter 0\\motion 0\\oldMsps 0"));

    //Load motors from the XDFL config file
    unsigned int count = parser.count("fabAtHomePrinter 0\\electronics 0\\motor");
    for(unsigned int i = 0; i < count; ++i)
    {
        string base = "fabAtHomePrinter 0\\electronics 0\\motor "+Util::toString(i)+"\\";
        string name = parser.text(base+"name 0");
        byte address = (byte)Util::assertType<unsigned int>(parser.text(base+"address 0"));
        double countsPerDistanceUnit = Util::assertType<double>(parser.text(base+"countsPerDistanceUnit 0"));
        short kp = Util::assertType<unsigned short>(parser.text(base+"kp 0"));
        short kd = Util::assertType<unsigned short>(parser.text(base+"kd 0"));
        short ki = Util::assertType<unsigned short>(parser.text(base+"ki 0"));
        short il = Util::assertType<unsigned short>(parser.text(base+"il 0"));
        byte ol = (byte)Util::assertType<unsigned int>(parser.text(base+"ol 0"));
        byte cl = (byte)Util::assertType<unsigned int>(parser.text(base+"cl 0"));
        short el = Util::assertType<unsigned short>(parser.text(base+"el 0"));
        byte sr = (byte)Util::assertType<unsigned int>(parser.text(base+"sr 0"));
        byte db = (byte)Util::assertType<unsigned int>(parser.text(base+"db 0"));
        double ticksPerSecond = Util::assertType<double>(parser.text(base+"ticksPerSecond 0"));
        motors[name] = Motor(name,address,countsPerDistanceUnit,ticksPerSecond,kp,kd,ki,il,ol,cl,el,sr,db);
        motors[name].setVelocity(100);
        motors[name].setAcceleration(100);
    }

    //Load axes from the XDFL file
    count = parser.count("fabAtHomePrinter 0\\axis");
    for(unsigned int i = 0; i < count; ++i)
    {
        string base = "fabAtHomePrinter 0\\axis "+Util::toString(i)+"\\";
        string name = parser.text(base+"name 0");
        string motorName = parser.text(base+"motorName 0");
        map<string, Motor, LessThanString>::iterator motor = motors.find(motorName);
        if(motors.find(motorName) == motors.end())
        {
            return "Axis "+name+" references motor "+motorName+" which has not been loaded.";
        }

        //THIS IS WHERE YOU REVERSE THE AXIS
        if(name.compare("Y") == 0 || name.compare("Z") == 0)
            //CHANGE MADE in v0.1 z should now be pos for down neg for up
        {
            motor->second.setReversed(true);
        }
        axes[name] = Axis(name,&(motor->second));
    }

    //Check that axes named X, Y, and Z were loaded.
    if(axes.find("X") == axes.end())
    {
        return "Must load an axis named X.";
    }
    if(axes.find("Y") == axes.end())
    {
        return "Must load an axis named Y.";
    }
    if(axes.find("Z") == axes.end())
    {
        return "Must load an axis named Z.";
    }

    //Load bays from the XDFL file
    count = parser.count("fabAtHomePrinter 0\\tool 0\\bay");
    for(unsigned int i = 0; i < count; ++i)
    {
        string base = "fabAtHomePrinter 0\\tool 0\\bay "+Util::toString(i)+"\\";
        string name = parser.text(base+"name 0");
        string motorName = parser.text(base+"motorName 0");
        if(motors.find(motorName) == motors.end())
        {
            return "Bay "+name+" references motor "+motorName+" which has not been loaded.";
        }
        double x = Util::assertType<double>(parser.text(base+"location 0\\x 0"));
        double y = Util::assertType<double>(parser.text(base+"location 0\\y 0"));
        double z = Util::assertType<double>(parser.text(base+"location 0\\z 0"));
        tool.bays[name] = Bay(name,Point(x,y,z),&(motors.find(motorName)->second));
        motors.find(motorName)->second.setVelocity(1);
    }

    //Check that at least one bay is loaded.
    if(tool.bays.size() == 0)
    {
        return "Must load at least one bay.";
    }

    //if the total number of axis motors and bay motors does not equal NUM_MODULES declared in the config file
    if (tool.bays.size() + axes.size() != NUM_MODULES)
        return "Invalid number of motors";

    return "";
}

string FabAtHomePrinter::loadFabFile(string filePath)
{
    //Load the file.
    TiXmlDocument file;
    if(!file.LoadFile(filePath.c_str()))
    {
        return "Could not interpret "+filePath+" as a xml file.";
    }

    //Clear previously loaded data.
    materialCalibrations.clear();
    model.paths.clear();

    TiXmlNode* root(file.RootElement());
    for(TiXmlNode* child = root->FirstChild(); child != NULL; child = root->IterateChildren(child))
    {
        if(strcmp(child->Value(), "materialCalibration") == 0)
        {
            loadMaterialCalibration(child);
        }
        else if(strcmp(child->Value(), "path") == 0)
        {
            loadPath(child);
        }
        else if(strcmp(child->Value(), "printAcceleration") == 0)
        {
            PRINT_ACCELERATION = Util::assertType<double>(child->FirstChild()->Value());
        }
    }
    return "";
}
string FabAtHomePrinter::state()
{
    if(printing)
    {
        return "PRINTING";
    }
    if(paused)
    {
        return "PAUSED";
    }
    return "IDLE";
}

bool FabAtHomePrinter::isPrinting()
{
    return printing;
}

bool FabAtHomePrinter::isPaused()
{
    return paused;
}

void FabAtHomePrinter::loadedMaterialCalibrations(vector<string>& result)
{
    for (map<string,MaterialCalibration,LessThanString>::iterator i = materialCalibrations.begin();
    i != materialCalibrations.end(); ++i)
    {
        result.push_back(i->first);
    }
}

void FabAtHomePrinter::loadMaterialCalibration(TiXmlNode* node)
{
    //Loads in the material calibration from the material specified in the Fab file
    string name = node->FirstChild("name")->FirstChild()->Value();
    double pathSpeed = Util::assertType<double>(node->FirstChild("pathSpeed")->FirstChild()->Value());
    double pathWidth = Util::assertType<double>(node->FirstChild("pathWidth")->FirstChild()->Value());
    double depositionRate = Util::assertType<double>(node->FirstChild("depositionRate")->FirstChild()->Value());
    double pushout = Util::assertType<double>(node->FirstChild("pushout")->FirstChild()->Value());
    double suckback = Util::assertType<double>(node->FirstChild("suckback")->FirstChild()->Value());
    double suckbackDelay = Util::assertType<double>(node->FirstChild("suckbackDelay")->FirstChild()->Value());
    double clearance = Util::assertType<double>(node->FirstChild("clearance")->FirstChild()->Value());
    int pausePaths = Util::assertType<int>(node->FirstChild("pausePaths")->FirstChild()->Value());
    double pitch = Util::assertType<double>(node->FirstChild("pitch")->FirstChild()->Value());
    materialCalibrations[name] = MaterialCalibration(name,
                                                     pathSpeed,
                                                     pathWidth,
                                                     depositionRate,
                                                     pushout,
                                                     suckback,
                                                     suckbackDelay,
                                                     clearance,
                                                     pausePaths,
                                                     pitch);
}

string FabAtHomePrinter::loadPath(TiXmlNode* node)
{
    vector<Point> points;

    //Load in path of points and material calibration from the Fab file
    string materialCalibrationName = node->FirstChild("materialCalibrationName")->FirstChild()->Value();
    if(materialCalibrations.find(materialCalibrationName) == materialCalibrations.end())
    {
        return "A path references material calibration "+materialCalibrationName+" which has not been loaded.";
    }
    for(TiXmlNode* child = node->FirstChild(); child != NULL; child = node->IterateChildren(child))
    {
        if(strcmp(child->Value(), "point") == 0)
        {
            double x = Util::assertType<double>(child->FirstChild("x")->FirstChild()->Value());
            double y = -Util::assertType<double>(child->FirstChild("y")->FirstChild()->Value());
            double z = Util::assertType<double>(child->FirstChild("z")->FirstChild()->Value());
            points.push_back(Point(x,y,z));
        }
    }
    model.paths.push_back(Path(&materialCalibrations[materialCalibrationName],points));
    return "";
}

Bay* FabAtHomePrinter::findBay(MaterialCalibration* materialCalibration)
{
    for(map<string,Bay,LessThanString>::iterator i = tool.bays.begin(); i != tool.bays.end(); ++i)
    {
        if(materialCalibration == i->second.materialCalibration)
        {
            return &(i->second);
        }
    }
    return NULL;
}

void FabAtHomePrinter::executePausePath(const Point& start)
{
    vector<Point> pausePathPoints(2);
    //Move the platform down when pause begins
    pausePathPoints.clear();
    pausePathPoints.push_back(start);
    pausePathPoints.push_back(Point(start.x, start.y, start.z + PLATFORM_DELTA));
    executePath(Path(NULL,pausePathPoints),NULL,false);

    paused = true;
    printing = false;

    callWarning("Execution has been paused.  Press Resume to continue execution.");
    //Stop the program temporarily until pauseSemaphore is released
    pauseSemaphore.acquire();

    printing = true;
    paused = false;

    //Move the platform back up when ready to resume printing.
    pausePathPoints.clear();
    pausePathPoints.push_back(Point(start.x, start.y, start.z + PLATFORM_DELTA));
    pausePathPoints.push_back(start);
    executePath(Path(NULL,pausePathPoints),NULL,false);
}

void FabAtHomePrinter::executeSetupPath(const Point& start, const Point& end, const double& clearance)
{
    vector<Point> setupPathPoints(4);
    setupPathPoints.clear();
    setupPathPoints.push_back(start);
    setupPathPoints.push_back(Point(start.x, start.y, start.z + clearance));
    setupPathPoints.push_back(Point(end.x, end.y, start.z + clearance));
    setupPathPoints.push_back(end);
    executePath(Path(NULL,setupPathPoints),NULL,false);
}


void FabAtHomePrinter::print()
{
    printing = true;
    pausePrintFlag = false;
    cancelPrintFlag = false;
    redoPathFlag = false;
    initializePathMode();
    int currentPath = 0;
    reportProgress(currentPath, displayText.c_str());

    //Iterate through the loaded paths and execute them.
    while(currentPath < model.paths.size())
    {
        Path path = model.paths[currentPath]; //Copy construct the path to be executed.


        //Find a bay with the required material calibration.
        Bay* bay = findBay(path.materialCalibration);
        while(bay == NULL)
        {
            //Prompt user to load required material calibration into a bay.
            callWarning("No bay has the required material calibration.  Press OK to pause execution.");
            Point start(axes["X"].motor->getPosition(),
                        axes["Y"].motor->getPosition(),
                        axes["Z"].motor->getPosition()); //The current position.
            executePausePath(start);
            bay = findBay(path.materialCalibration);
        }

        //Apply bay offset to path.
        for(vector<Point>::iterator j = path.points.begin(); j != path.points.end(); ++j)
        {
            j->x -= bay->location.x;
            j->y -= bay->location.y;
            j->z -= bay->location.z;
        }

        //Update the display text.

        displayText = "Executing setup path.";
        reportProgress(currentPath, displayText.c_str());

      	//Move from the current position to the beginning of the current path.
        Point start(axes["X"].motor->getPosition(),
                    axes["Y"].motor->getPosition(),
                    axes["Z"].motor->getPosition()); //The current position.
        Point end = path.points[0]; //The first point of the current path.
        executeSetupPath(start, end, path.materialCalibration->CLEARANCE);

        //Update the display text.

        displayText = "Executing path "+Util::toString<int>
                      (currentPath+1)+" of "+Util::toString<int>(model.paths.size())+".";
        reportProgress(currentPath, displayText.c_str());


        //Execute the current path.
        executePath(path,bay,true);

        ++(path.materialCalibration->pathsExecuted);
        //Increment the number of paths executed by the material calibration.

        if(cancelPrintFlag)
        {
            //Cancel the print.
            break;
        }
        if((path.materialCalibration->pathsExecuted % (int)(path.materialCalibration->PAUSE_PATHS)) == 0)
        {
            //An automatic pause has been trigger.
            pausePrintFlag = true;
        }
        if(pausePrintFlag)
        {
            //Process a manual or automatic pause.
            executePausePath(path.points[path.points.size()-1]);
            pausePrintFlag = false;
        }
        if(redoPathFlag)
        {
            //Redo the current path.
            redoPathFlag = false;
        }
        else
        {
            //Move on to the next path.
            currentPath++;
            reportProgress(currentPath, displayText.c_str());
        }
    }

    //Update the display text.
    if (cancelPrintFlag)
    {
        cancelPrintFlag = false;
        displayText = "Fabrication cancelled.";
    }
    else
    {
        displayText = "Fabrication successfully completed.";
    }
    reportProgress(currentPath, displayText.c_str());
    //Execution has stopped.  Move the platform down.
    Point start(axes["X"].motor->getPosition(), axes["Y"].motor->getPosition(), axes["Z"].motor->getPosition());
    //The current position.

    Point end(start.x, start.y, start.z + PLATFORM_DELTA);
    executeSetupPath(start,end,0);
    printing = false;
    resetPos();
    finishedPrinting();
}


void FabAtHomePrinter::executePath(const Path& path, Bay* bay, const bool flowDuringPath)
{
    if(flowDuringPath)
    {
        //Want to achieve a steady state during path execution so scale the path speed if necessary.
        //Copied from model 1 code.
        double scaledPathSpeed = path.materialCalibration->PATH_SPEED;
        //pathdur is the duration of the path in seconds from nominal start of material flow to stop.
        double pathdur = path.length / path.materialCalibration->PATH_SPEED +
                         path.materialCalibration->SUCKBACK +
                         path.materialCalibration->SUCKBACK_DELAY;
        //Check for problematic path too short to reach steady state.
        double ssDur = path.materialCalibration->SUCKBACK +
                       path.materialCalibration->SUCKBACK_DELAY +
                       10 * path.materialCalibration->PATH_WIDTH/path.materialCalibration->PATH_SPEED;
        //Try to estimate duration of a path which reaches steady state.

        if(pathdur < ssDur)
        {
            scaledPathSpeed *= pathdur/ssDur;
        }

        //Calculate motion values.
        double suckpathdist = (path.materialCalibration->SUCKBACK -
                               path.materialCalibration->SUCKBACK_DELAY) * scaledPathSpeed;
        //suckpathdist is the distance from the end of the path at which to start suckback.


        //todo: find another way of calculating when to pusout and suckback
        double pathLengthWithoutSuckback = path.length - suckpathdist;
        double pushoutDistance = path.materialCalibration->PUSHOUT * OLD_MSPS * path.materialCalibration->PITCH;
        double pushoutVelocity = path.materialCalibration->PUSHOUT == 0 ? 0 :
                                 pushoutDistance / path.materialCalibration->PUSHOUT;
        double suckbackDistance = path.materialCalibration->SUCKBACK * OLD_MSPS * path.materialCalibration->PITCH;
        double suckbackVelocity = path.materialCalibration->SUCKBACK == 0 ? 0 :
                                  suckbackDistance / path.materialCalibration->SUCKBACK;
        double standardDistance = pathLengthWithoutSuckback * path.materialCalibration->DEPOSITION_RATE;
        double timeUntilSuckback = pathLengthWithoutSuckback / scaledPathSpeed;
        double standardVelocity = standardDistance / timeUntilSuckback;

        //Calculate where suckback begins.
        Point suckbackPoint;
        if(pathLengthWithoutSuckback >= path.length)
        {
            suckbackPoint = path.points[path.points.size()-1];
        }
        else
        {
            double beforeSuckbackLength = 0;
            vector<Point>::const_iterator i = path.points.begin();
            for(; beforeSuckbackLength + Point::calcDist(*i, *(i+1)) <= pathLengthWithoutSuckback; ++i)
            {
                beforeSuckbackLength += Point::calcDist(*i, *(i+1));
            }
            //Suckback should start somewhere on the line with endpoints *i and *(i+1).
            double diff = pathLengthWithoutSuckback - beforeSuckbackLength;
            double length = Point::calcDist(*i, *(i+1));
            Point v((i+1)->x - i->x, (i+1)->y - i->y, (i+1)->z - i->z); //v is the vector from *i to *(i+1).
            Point vDirection = Point(v.x/length, v.y/length, v.z/length);
            suckbackPoint = Point(i->x+diff*vDirection.x, i->y+diff*vDirection.y, i->z+diff*vDirection.z);
        }

        //Execute the path.
        SetFeedrate((float)scaledPathSpeed); //Feedrate is the path speed.
        executePoints(path.points,
                      bay,
                      flowDuringPath,
                      pushoutDistance,
                      pushoutVelocity,
                      standardDistance,
                      standardVelocity,
                      suckbackDistance,
                      suckbackVelocity,
                      suckbackPoint);
        //Wait for axis movement to finish.
        axes["X"].motor->waitMove();
     	axes["Y"].motor->waitMove();
     	axes["Z"].motor->waitMove();
        bay->motor->waitMove(); //Wait for bay movement to finish.
    }
    else
    {
        //No flow during path.
        SetFeedrate(10); //Feedrate is the path speed.
        executePoints(path.points,NULL,flowDuringPath,0,0,0,0,0,0,Point());
        //Wait for axis movement to finish.
        axes["X"].motor->waitMove();
        axes["Y"].motor->waitMove();
        axes["Z"].motor->waitMove();
    }
}

void FabAtHomePrinter::executePoints(const vector<Point>& points,
                                     Bay* bay,
                                     const bool flowDuringPath,
                                     double pushoutDistance,
                                     double pushoutVelocity,
                                     double standardDistance,
                                     double standardVelocity,
                                     double suckbackDistance,
                                     double suckbackVelocity,
                                     const Point& suckbackPoint)
{
    int currIndex = 0;
    int res = -1;
    bool flowStarted = false;
    while(res != points.size()-1)
    {
        //Invariant: currIndex is the next index to be added to the segment list.
        res = fillSegmentList(points, currIndex);
        //Invariant: res is the most recent index that was added to the segment list.
        //The segment list has been filled so start downloading.
        downloadSegmentList(bay,
                            flowDuringPath && !flowStarted,
                            flowDuringPath && res == points.size()-1,
                            pushoutDistance,
                            pushoutVelocity,
                            standardDistance,
                            standardVelocity,
                            suckbackDistance,
                            suckbackVelocity,
                            suckbackPoint);
        flowStarted = flowDuringPath;
        //The next index to be added to the segment list is the most recent index that was added to the segment list.
        currIndex = res;
    }
}

int FabAtHomePrinter::fillSegmentList(const vector<Point>& points, const int startIndex)
{
    if(points.size() == 0)
    {
        return -1;
    }
    ClearSegList((float)points[startIndex].x, (float)points[startIndex].y, (float)points[startIndex].z);
    for(unsigned int i = startIndex+1; i < points.size(); ++i)
    {
        int res = AddLineSeg((float)points[i].x, (float)points[i].y, (float)points[i].z);
        if(res == -1)
        {
            //points[i-2], points[i-1], and points[i] form two consecutive line segments that are not tangent.
            //Stop at points[i-1].
            return i-1;
        }
        if(res == -2)
        {
            //The segment list is full.
            return i-1;
        }
    }
    //All points have been inserted.
    return points.size()-1;
}

void FabAtHomePrinter::downloadSegmentList(Bay* bay,
                                           const bool startFlow,
                                           bool startSuckback,
                                           double pushoutDistance,
                                           double pushoutVelocity,
                                           double standardDistance,
                                           double standardVelocity,
                                           double suckbackDistance,
                                           double suckbackVelocity,
                                           const Point& suckbackPoint)
{

    InitPath();
    if(startFlow)
    {
        bay->motor->moveAbsolute(bay->motor->getCommandedPosition()-pushoutDistance,
                                 pushoutVelocity,
                                 PRINT_ACCELERATION); //Start pushout.
    }
    if (AddPathPoints() == -2)
        qDebug() << "error adding points"; //Start movement.
    if(startFlow)
    {
        bay->motor->waitMove(); //Wait for bay movement to finish.
        bay->motor->moveAbsolute(bay->motor->getCommandedPosition()-standardDistance,
                                 standardVelocity,
                                 PRINT_ACCELERATION); //Start standard flow.
    }

    //Move points to the path pointer buffer while handling suckback.
    double currX, currY, xDiff, yDiff;
    bool doneAddingPoints = false;
    while(!doneAddingPoints || startSuckback)
    {
        if(!doneAddingPoints && AddPathPoints() == -1)
        {
            doneAddingPoints = true;
        }
        if(startSuckback)
        {
            currX = axes["X"].motor->getPosition();
            currY = axes["Y"].motor->getPosition();
            xDiff = suckbackPoint.x - currX;
            yDiff = suckbackPoint.y - currY;

            if(xDiff*xDiff+yDiff*yDiff < 0.25)
            //If the head gets close enough to the end of the path, start the suckback early while possible
            {
                bay->motor->moveAbsolute(bay->motor->getCommandedPosition()+suckbackDistance,
                                         suckbackVelocity,
                                         PRINT_ACCELERATION); //Start suckback.
                startSuckback = false;
            }

        }
        if(startSuckback && !axes["X"].motor->moving()
            && !axes["Y"].motor->moving()
            && !axes["Z"].motor->moving())
            {
            //We have not started suckback and have reached end of path so we may have tunneled
            //through the suckback circle.  Just do the suckback now.
            bay->motor->moveAbsolute(bay->motor->getCommandedPosition()+suckbackDistance,
                                     suckbackVelocity,
                                     PRINT_ACCELERATION); //Start suckback.
            startSuckback = false;
        }

    }
}

bool FabAtHomePrinter::cleanUp()
{
    bool result;
    if(initialized)
    {
        //Perform cleanup for all motors.
        bool result = true;
        for(map<string,Motor,LessThanString>::iterator i = motors.begin(); i != motors.end(); ++i)
        {
            result = result && i->second.cleanUp();
        }
        if(result)
        {
            NmcShutdown();
            initialized = false;
        }
    }
    else
    {
        result = true;
    }
    return result;
}

FabAtHomePrinter::~FabAtHomePrinter()
{
    cleanUp();
}


void FabAtHomePrinter::stopMotors()
{
    //Stop all motors.
    axes["X"].motor->stop();
    axes["Y"].motor->stop();
    axes["Z"].motor->stop();
    int numLoadedBays = this->numLoadedBays();
    if(numLoadedBays >= 1)
    {
        tool.bays["Bay 0"].motor->stop();
    }
    if(numLoadedBays >= 2)
    {
        tool.bays["Bay 1"].motor->stop();
    }
    if(numLoadedBays >= 3)
    {
        tool.bays["Bay 2"].motor->stop();
    }
}

void FabAtHomePrinter::resetPos()
{
    //Reset position of all motors.
    axes["X"].motor->resetPosition();
    axes["Y"].motor->resetPosition();
    axes["Z"].motor->resetPosition();
    int numLoadedBays = this->numLoadedBays();
    if(numLoadedBays >= 1)
    {
        tool.bays["Bay 0"].motor->resetPosition();
    }
    if(numLoadedBays >= 2)
    {
        tool.bays["Bay 1"].motor->resetPosition();
    }
    if(numLoadedBays >= 3)
    {
        tool.bays["Bay 2"].motor->resetPosition();
    }
}
void FabAtHomePrinter::reset()
{
    NmcHardReset(X_Y_Z_GROUP_ADDRESS);
}

bool FabAtHomePrinter::isInitialized()
{
    return initialized;
}

//Checks to see if the bay, represented by str_motor, is contained in the list of bays.
bool FabAtHomePrinter::contains(string str_motor)
{
    map<string, Bay, LessThanString> new_map = this->tool.bays;
    return new_map.find(str_motor) != new_map.end();
}

bool FabAtHomePrinter::containsMaterial(string cur_material)
{
    return materialCalibrations.find(cur_material) != materialCalibrations.end();
}

void FabAtHomePrinter::moveMotor(string str_motor, double distance)
{
    /**
    if (contains(str_motor))
        motors[str_motor].move(distance,
                               motors[str_motor].getVelocity(),
                               motors[str_motor].getAcceleration());
    */
}
