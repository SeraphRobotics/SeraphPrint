#ifndef VMTESTER_H
#define VMTESTER_H
#include "virtualmachines.h"


class VMTester
{
public:
    VMTester();

    bool connectVM();

    bool NPathTest();
    bool moveTest();
    bool moveToTest();


//    TestPrinter vm;
    VirtualPrinter vm;
    QString configFilePath;
    QString comport;
};

#endif // VMTESTER_H
