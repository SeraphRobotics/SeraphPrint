#ifndef PRINTTHREAD_H
#define PRINTTHREAD_H

#include <QThread>
#include "FabAtHomePrinter.h"

//A thread to handle printing.
namespace PROJECT_NAMESPACE
{

class PrintThread : public QThread
{
    Q_OBJECT

public:
    PrintThread();
    PrintThread(FabAtHomePrinter *newPrinter);
    ~PrintThread();

    /**
      Tells the printer to print in a separate thread
     */
    void run();

signals:

    void printDone();

private:
    FabAtHomePrinter* printer; //The printer object with the current settings from the configuration and fab files
};

}


#endif // PRINTTHREAD_H
