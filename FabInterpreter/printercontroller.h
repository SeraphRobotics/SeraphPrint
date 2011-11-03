#ifndef PRINTERCONTROLLER_H
#define PRINTERCONTROLLER_H

#include "FabAtHomePrinter.h"
#include "mainwindow.h"



//A thread to handle printing.
class PrintThread : public QThread
{
    Q_OBJECT

public:
    PrintThread();
    PrintThread(FabAtHomePrinter* newPrinter): printer(newPrinter){};

private:

    FabAtHomePrinter* printer;

protected:
    void run()
    {
        //printer->print();
    }
};


//A thread to handle GUI components.
class GUIComponentsThread : public QThread
{
    Q_OBJECT

protected:
    bool keepGoing;


public:
    GUIComponentsThread():keepGoing(false)
    {
    }

    void stop()
    {
        keepGoing = false;
    }

protected:
    void run()
    {
        while(keepGoing)
        {
        }
    }
};



class PrinterController
{
    Q_OBJECT
public:
    PrinterController();
    PrinterController(MainWindow* newWindow, FabAtHomePrinter *newPrinter);
    void reportPrintProgress();

private:
    MainWindow* window;
    FabAtHomePrinter* printer;


    //thread safe variables
    double posDisplayPeriod; //Number of seconds between position updates in user interface.
    bool enablePosDisplay;
    string pathDisplayText;
    int maxProgress;
};

#endif // PRINTERCONTROLLER_H
