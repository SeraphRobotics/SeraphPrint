#ifndef VMTESTER_H
#define VMTESTER_H
#include "virtualmachines.h"


class VMTester
{
public:
    VMTester();

    bool connectVM();

    bool movementTest();


//    TestPrinter vm;
    VirtualPrinter vm;
    QString configFilePath;
    QString comport;
};

#endif // VMTESTER_H
