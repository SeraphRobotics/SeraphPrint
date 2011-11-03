#include "printthread.h"
#include "Interface.h"

PrintThread::PrintThread(){}
PrintThread::PrintThread(FabAtHomePrinter* newPrinter):
        printer(newPrinter){}

PrintThread::~PrintThread()
{
}

void PrintThread::run()
{
    printer->print();
    emit printDone();
}
