#include <iostream>
#include <QInputDialog>
#include <QDir>
#include "Interface.h"

using namespace std;

Interface::Interface()
{
    printer = new FabAtHomePrinter();
    pThread = new PrintThread(printer);
    currentStage = NOT_INITIALIZED;
    isPaused = false;
}


bool Interface::loadConfigFile(QString file, QString port)
{
    string str_file = file.toStdString();
    string str_port = port.toStdString();
    if (currentStage == NOT_INITIALIZED)
    {
        string str = printer->initialize(str_file, str_port);
        if (str.compare("") == 0)
        {
            currentStage = CONFIG_LOADED;
            cout << str << endl;
            return true;
        }
        else
        {
            cout << str << endl;
            return false;
        }
    }
    else {

        callWarning("Cannot load a config file at this time\n");
        cout << "Cannot load now" << endl;
        return false;
    }

}

bool Interface::loadConfigFile(QString file)
{
    QDir d("/dev");
    QRegExp expMac("tty.usbserial-");
    QRegExp expLinux("ttyUSB"); //get more info from Andy
    QStringList l = d.entryList(QDir::System);
    QStringList l1 = l.filter(expMac);
    QStringList l2 = l.filter(expLinux);
    QString port = "/dev/";
    if (l1.size() > 0)
        port = port + l1.at(0);
    else if (l2.size() > 0)
        port = port + l2.at(0);
    return loadConfigFile(file, port);
}

void Interface::print()
{
    if (currentStage == MODEL_FILE_LOADED)
    {
        if (pThread != NULL) delete pThread;
        pThread = new PrintThread(printer);
        connect(pThread, SIGNAL(printDone()), this, SLOT(donePrinting()), Qt::DirectConnection);
        pThread->start();
        currentStage = PRINTING;
    }
    else {
        callWarning("Cannot print since model file is not loaded\n");
    }

}

void Interface::donePrinting()
{
    currentStage = CONFIG_LOADED;
}

QString Interface::getState()
{
    QString state;
    switch (currentStage){
        case NOT_INITIALIZED:
            state = "Not Initialized";
            break;
        case CONFIG_LOADED:
            state = "Config Loaded";
            break;
        case MODEL_FILE_LOADED:
            state = "Model File Loaded";
            break;
        case PRINTING:
            state = "Printing";
            break;
        default:
            state = "Unrecognized State";
            break;
    }
    return state;

}

bool Interface::loadFabFile(QString filePath)
{
    string str_filePath = filePath.toStdString();
    if (currentStage == CONFIG_LOADED)
    {
        string str = printer->loadFabFile(str_filePath);
        if (str.compare("") == 0)
        {
            currentStage = MODEL_FILE_LOADED;
            vector<string> loadedMaterials;
            printer->loadedMaterialCalibrations(loadedMaterials);
            for(vector<string>::iterator i = loadedMaterials.begin(); i != loadedMaterials.end(); ++i)
            {
                printer->bayMaterials.append(i->c_str());
            }
            string bay0 = "Bay 0";
            string bay1 = "Bay 1";
            string bay2 = "Bay 2";
            int numBays = printer->numLoadedBays();
            if (numBays <= 1)
                printer->equipBay(bay0, printer->bayMaterials.at(0));
            else if (numBays <= 2)
                printer->equipBay(bay1, printer->bayMaterials.at(0));
            else
                printer->equipBay(bay2, printer->bayMaterials.at(0));
            return true;
        }
        else return false;
    }
    else return false;
}


int Interface::numLoadedPaths()
{
    if (currentStage == MODEL_FILE_LOADED || currentStage == PRINTING)
        return printer->numLoadedPaths();
    else return -1;
}

int Interface::numLoadedBays()
{
    if (currentStage != NOT_INITIALIZED)
        return printer->numLoadedBays();
    else return -1;
}

bool Interface::move(double x, double y, double z)
{
    if (currentStage != NOT_INITIALIZED && currentStage != PRINTING)
    {
        Motor *x_motor = printer->axes["X"].motor;
        Motor *y_motor = printer->axes["Y"].motor;
        Motor *z_motor = printer->axes["Z"].motor;
        return x_motor->moveRelative(x, x_motor->getVelocity(), x_motor->getAcceleration()) &&
                y_motor->moveRelative(y, y_motor->getVelocity(), y_motor->getAcceleration()) &&
                z_motor->moveRelative(z, z_motor->getVelocity(), z_motor->getAcceleration());
    }
    else return false;
}

bool Interface::moveAbsolute(double x, double y, double z)
{
    if (currentStage != NOT_INITIALIZED && currentStage != PRINTING)
    {
        Motor *x_motor = printer->axes["X"].motor;
        Motor *y_motor = printer->axes["Y"].motor;
        Motor *z_motor = printer->axes["Z"].motor;
        return (x_motor->moveAbsolute(x, x_motor->getVelocity(), x_motor->getAcceleration()) &&
                y_motor->moveAbsolute(y, y_motor->getVelocity(), y_motor->getAcceleration()) &&
                z_motor->moveAbsolute(z, z_motor->getVelocity(), z_motor->getAcceleration()));
    }
    else return false;
}

bool Interface::moveBayMotor(int bay, double distance)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string stdstr_bay = "Bay " + QString::number(bay, 10).toStdString();
        if (printer->contains(stdstr_bay))
        {
            Motor* cur_motor = printer->tool.bays[stdstr_bay].motor;
            return cur_motor->moveRelative(distance, cur_motor->getVelocity(), cur_motor->getAcceleration());
        }
    }
    return false;
}

bool Interface::moveAbsoluteBayMotor(int bay, double distance)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string stdstr_bay = "Bay " + QString::number(bay, 10).toStdString();
        if (printer->contains(stdstr_bay))
        {
            Motor* cur_motor = printer->tool.bays[stdstr_bay].motor;
            return cur_motor->moveAbsolute(distance, cur_motor->getVelocity(), cur_motor->getAcceleration());
        }
    }
    return false;
}


double Interface::getVelocity(QString motor)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string strMotor = motor.toStdString();
        if (strMotor.compare("X") == 0 || strMotor.compare("Y") == 0 || strMotor.compare("Z") == 0)
        {
            return printer->axes[strMotor].motor->getVelocity();
        }
    }
    return -1.0;
}

double Interface::getAcceleration(QString motor)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string strMotor = motor.toStdString();
        if (strMotor.compare("X") == 0 || strMotor.compare("Y") == 0 || strMotor.compare("Z") == 0)
        {
            return printer->axes[strMotor].motor->getAcceleration();
        }
    }
    return -1.0;
}

double Interface::getBayVelocity(int bay)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string str_bay = "Bay " + QString::number(bay, 10).toStdString();
        if (currentStage != NOT_INITIALIZED)
        {
            if (printer->contains(str_bay))
            {
                return printer->tool.bays[str_bay].motor->getVelocity();
            }
        }
    }
    return -1.0;
}


double Interface::getBayAcceleration(int bay)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string str_bay = "Bay " + QString::number(bay, 10).toStdString();
        if (printer->contains(str_bay))
        {
            return printer->tool.bays[str_bay].motor->getAcceleration();
        }
    }
    return -1.0;
}


bool Interface::setVelocity(QString motor, double velocity)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string strMotor = motor.toStdString();
        if (strMotor.compare("X") == 0 || strMotor.compare("Y") == 0 || strMotor.compare("Z") == 0)
        {
            printer->axes[strMotor].motor->setVelocity(velocity);
            return true;
        }
    }
    return false;
}

bool Interface::setAcceleration(QString motor, double acceleration)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string strMotor = motor.toStdString();
        if (strMotor.compare("X") == 0 || strMotor.compare("Y") == 0 || strMotor.compare("Z") == 0)
        {
            printer->axes[strMotor].motor->setAcceleration(acceleration);
            return true;
        }
    }
    return false;
}

bool Interface::setBayVelocity(int bay, double velocity)
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        string str_bay = "Bay " + QString::number(bay, 10).toStdString();
        if (currentStage != NOT_INITIALIZED)
        {
            if (printer->contains(str_bay))
            {
                printer->tool.bays[str_bay].motor->setVelocity(velocity);
                return true;
            }
        }
    }
    return false;
}


bool Interface::setBayAcceleration(int bay, double acceleration)
{
    string str_bay = "Bay " + QString::number(bay, 10).toStdString();
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        if (printer->contains(str_bay))
        {
            printer->tool.bays[str_bay].motor->setAcceleration(acceleration);
            return true;
        }
    }
    return false;
}

bool Interface::equipMaterial(int bay, QString material)
{
    if (currentStage == MODEL_FILE_LOADED)
    {
        string str_bay = "Bay " + QString::number(bay, 10).toStdString();
        string str_material = material.toStdString();
        if (printer->contains(str_bay) && printer->containsMaterial(str_material))
        {
            printer->equipBay(str_bay, str_material);
            return true;
        }
    }
    return false;
}

bool Interface::pausePrint()
{
    if (currentStage == PRINTING)
    {
        printer->pausePrint();
        isPaused = true;
        return true;
    }
    return false;
}

bool Interface::resumePrint()
{
    if (currentStage == PRINTING && isPaused)
    {
        printer->resumePrint();
        isPaused = false;
        return true;
    }
    return false;
}

bool Interface::cancelPrint()
{
    if (currentStage == PRINTING)
    {
        printer->cancelPrint();
        return true;
    }
    return false;
}

double Interface::getX()
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        return printer->axes["X"].motor->getPosition();
    }
    return -1;
}

double Interface::getY()
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        return printer->axes["Y"].motor->getPosition();
    }
    return -1;
}

double Interface::getZ()
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        return printer->axes["Z"].motor->getPosition();
    }
    return -1;
}


bool Interface::removeConfig()
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        disconnect(pThread, SIGNAL(printDone()), this, SLOT(donePrinting()));
        delete pThread;
        delete printer;
        currentStage = NOT_INITIALIZED;
        return true;
    }
    return false;
}

bool Interface::redoPath(void)
{
    if (currentStage == PRINTING)
    {
        printer->redoPath();
        return true;
    }
    return false;
}


bool Interface::stopMotors()
{
    if (currentStage != NOT_INITIALIZED)
    {
        printer->stopMotors();
        return true;
    }
    return false;
}


bool Interface::resetPos()
{
    if (currentStage == CONFIG_LOADED || currentStage == MODEL_FILE_LOADED)
    {
        printer->resetPos();
        return true;
    }
    return false;
}

int Interface::currentPath()
{
    if (currentStage == PRINTING)
        return 1;
    else return -1;
}

QString Interface::getMaterial(int bay)
{
    string str_bay = "Bay " + QString::number(bay, 10).toStdString();
    if (currentStage == MODEL_FILE_LOADED || currentStage == PRINTING)
    {
        if (printer->contains(str_bay))
        {
            return QString::fromStdString(printer->tool.bays.at(str_bay).materialCalibration->NAME);
        }
    }
    return "";
}
