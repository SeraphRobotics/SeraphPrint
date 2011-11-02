# -------------------------------------------------
# Project created by QtCreator 2009-11-17T16:48:37
# ------------------------------------------------
INCLUDEPATH += ./Common/tinyxml
HEADERS += ./FabInterpreter/Point.h \
    ./FabInterpreter/InterpreterPath.h \
    ./FabInterpreter/Motor.h \
    ./FabInterpreter/Model.h \
    ./FabInterpreter/MaterialCalibration.h \
    ./FabInterpreter/FabAtHomePrinter.h \
    ./FabInterpreter/Bay.h \
    ./FabInterpreter/Axis.h \
    ./FabInterpreter/Util.h \
    ./FabInterpreter/Tool.h \
    ./FabInterpreter/printthread.h \
    ./FabInterpreter/Interface.h
SOURCES += ./FabInterpreter/Point.cpp \
    ./FabInterpreter/InterpreterPath.cpp \
    ./FabInterpreter/Motor.cpp \
    ./FabInterpreter/Model.cpp \
    ./FabInterpreter/MaterialCalibration.cpp \
    ./FabInterpreter/FabAtHomePrinter.cpp \
    ./FabInterpreter/Bay.cpp \
    ./FabInterpreter/Axis.cpp \
    ./FabInterpreter/Tool.cpp \
    ./FabInterpreter/printthread.cpp \
    ./FabInterpreter/Interface.cpp

#CONFIG(debug, debug|release):TARGET = ./Libraries/fabcontrold
#else:TARGET = ./Libraries/fabcontrol
win32 {
    include("jrkerr-windows.pro")
    INCLUDEPATH += ./Common/Windows/JrKerr
}

unix {
    include("jrkerr-posix.pro")
    INCLUDEPATH += ./Common/Posix/JrKerr
}
include("tinyxml.pro")
include("src.pro")
