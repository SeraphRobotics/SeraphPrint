
# event driven device enumeration on windows requires the gui module
#!win32:QT               -= gui

#OBJECTS_DIR             += ./Common/JrKerr/tmp
#MOC_DIR                 += ./Common/JrKerr/tmp
DEPENDDIR              += ./Common/Posix/JrKerr/src/
INCLUDEDIR             += ./Common/Posix/JrKerr/src/ ./Common/Posix/JrKerr/tmp
    HEADERS                += ./Common/Posix/JrKerr/src/qextserialport.h \
                              ./Common/Posix/JrKerr/src/qextserialport_p.h \
                              ./Common/Posix/JrKerr/src/qextserialenumerator.h \
                              ./Common/Posix/JrKerr/src/qextserialenumerator_p.h \
                              ./Common/Posix/JrKerr/src/qextserialport_global.h
    SOURCES                += ./Common/Posix/JrKerr/src/qextserialport.cpp \
                              ./Common/Posix/JrKerr/src/qextserialenumerator.cpp
    unix:SOURCES           += ./Common/Posix/JrKerr/src/qextserialport_unix.cpp
    unix:!macx:SOURCES     += ./Common/Posix/JrKerr/src/qextserialenumerator_unix.cpp
    macx:SOURCES           += ./Common/Posix/JrKerr/src/qextserialenumerator_osx.cpp
    win32:SOURCES          += ./Common/Posix/JrKerr/src/qextserialport_win.cpp \
                              ./Common/Posix/JrKerr/src/qextserialenumerator_win.cpp

    # For Windows user who doesn't have Qt's Private files
    win32{
        DEFINES            += QESP_NO_QT_PRIVATE
        HEADERS            += ./Common/Posix/JrKerr/src/qextwineventnotifier_p.h
        SOURCES            += ./Common/Posix/JrKerr/src/qextwineventnotifier_p.cpp
    }

macx:LIBS              += -framework IOKit -framework CoreFoundation
win32:LIBS             += -lsetupapi -ladvapi32 -luser32
