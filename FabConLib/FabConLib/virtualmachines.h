#ifndef VIRTUALMACHINEENVIROMENT_H
#define VIRTUALMACHINEENVIROMENT_H

#include <QScriptEngine>
#include <QDomDocument>
#include "bay.h"
#include "xyzmotion.h"
#include "arduinointerface.h"

class VMPrototype:public QObject
    {
    Q_OBJECT
    public:
        VMPrototype();

        QScriptEngine* makeEngine();

    public slots:
        /**
         * Sets the override COM port for the VM which will be used in loadConfig.
         */
        void setComPort(QString comPort);
        /**
         * @return true if loadConfig() succeeded.
         */
        bool isInitialized();

        /// These methods should be overriden by actual VM and test VM classes.

        /**
         * Builds a virtual machine based on the QDomDocument.
         * Allows the document to be build by a handler program rather than a file.
         */
        virtual void loadConfig(QDomDocument document);
        /**
         * @return a string of all errors.
         */
        virtual QString getErrors();
        /**
         * Used to limit the reach of the upper level code.
         * @return true if path is valid and queued.
         */
        QVector<double> currentPosition();

        void runCmds(QStringList sl);

        bool moveTo(double x, double y, double z, double speed);
        bool move(double x, double y, double z, double speed);

        bool forceStop();

        virtual void resetPosition();

    public:

        QList<Bay*> bays;
        XYZMotion* xyzmotion;

    protected:
        QString comPort_;
        QString error_string_;
        bool initialized_;
    };



class VirtualPrinter:public VMPrototype
{
    Q_OBJECT
public:
    VirtualPrinter();

public slots:
    void loadConfig(QDomDocument document);
    QString getErrors();

    void runCmds(QStringList sl);
    bool moveTo(double x, double y, double z, double speed);
    bool move(double x, double y, double z, double speed);

    bool forceStop();
    void resetPosition();

public:
    ArduinoInterface* ai_;

//public:
//    ElectronicsInterface eInterface; //TODO: this should be private. Nothing above VM should access it.
};



class TestPrinter:public VMPrototype
{
    Q_OBJECT
public:
    TestPrinter();


public slots:
    void loadConfig(QDomDocument document);

    void dumpstates();
    void resetPosition();
    void runCmds(QStringList sl);
    bool moveTo(double x, double y, double z, double speed);
    bool move(double x, double y, double z, double speed);

    bool forceStop();

private:
    QStringList totalprintcommands_;
};


/**
 * Runs a script with access to motors and coordinated motion instances.
 */
QString runScript(VirtualPrinter *vm, QString script_);

#endif // VIRTUALMACHINEENVIROMENT_H
