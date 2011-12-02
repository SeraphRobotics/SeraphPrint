#ifndef VIRTUALMACHINEENVIROMENT_H
#define VIRTUALMACHINEENVIROMENT_H

#include <QThread>
#include "motor.h"
#include <QScriptEngine>
#include <QDomDocument>
#include "electronicsinterface.h"
#include "bay.h"
#include "jscmotion.h"
#include "xyzmotion.h"
#include "jsxyz.h"

class VMPrototype:public QObject
    {
    Q_OBJECT
    public:
        VMPrototype();

        QScriptEngine* makeEngine();


    public slots:
        /**
         *sets the overide comport for the VM which will be used in loadConfig
         */
        void setComPort(QString comPort);
        /**
         * @return true if initialized loadConfig succeeded
         */
        bool isInitialized();
        /**
         * used to limit the reach of the upper level code
         * @return the size of a valize NPath
         */
        int nstatesize();



        /// TO be overideed by the actual VM and the test VM

        /**
         *builds a virtual machine based on the QDomDocument
         *allows the document to be build by a handler program rather than a file
         */
        void loadConfig(QDomDocument document);
        /**
         * @return a string of all objects errors
         */
        virtual QString getErrors();
        /**
         * used to limit the reach of the upper level code
         * @return true if path is valid and queued
         */
        virtual bool executeNPath(NPath path);


    public:
        QList<Bay*> bays;
        XYZMotion* xyzmotion;

    protected:
        QString comPort_;
        bool initialized_;
        int statesize_;
        QString error_string_;
        JsXYZ jsxyz_;

        QMap<int,int> idtostatemap_;
        int frequency_;

    };



class VirtualPrinter:public VMPrototype
{
    Q_OBJECT
public:
    VirtualPrinter();

public slots:
    /**
     *builds a virtual machine based on the QDomDocument
     *allows the document to be build by a handler program rather than a file
     */
    void loadConfig(QDomDocument document);
    /**
     * @return a string of all objects errors
     */
    QString getErrors();

    /**
     * used to limit the reach of the upper level code
     * @return true if path is valid and queued
     */
    bool executeNPath(NPath path);

public:
    ElectronicsInterface eInterface;//TODO: this should ne private. Nothing above VM should access it.
};



class TestPrinter:public VMPrototype
{
    Q_OBJECT
public:
    TestPrinter();
    void dumpstates();

public slots:
    /**
     *builds a virtual machine based on the QDomDocument
     *allows the document to be build by a handler program rather than a file
     */
    void loadConfig(QDomDocument document);

    /**
     * used to limit the reach of the upper level code
     * @return true if path is valid and queued
     */
    bool executeNPath(NPath path);

private:
    QList<NPath> totalprintcommands_;
};




/**
 * runs a script with access to motors and coordinated motion instances.
 */
QString runScript(VirtualPrinter *vm, QString script_);

#endif // VIRTUALMACHINEENVIROMENT_H
