
# event driven device enumeration on windows requires the gui module
#!win32:QT               -= gui

#OBJECTS_DIR             += ./JrkerrElectronics/JrKerr/tmp
#MOC_DIR                 += ./JrkerrElectronics/JrKerr/tmp
DEPENDDIR              += ./JrkerrElectronics/Posix/qextserial/
INCLUDEDIR             += ./JrkerrElectronics/Posix/qextserial/ ./JrkerrElectronics/Posix/qextserial/tmp
    HEADERS                += ./JrkerrElectronics/Posix/qextserial/qextserialport.h \
                              ./JrkerrElectronics/Posix/qextserial/qextserialport_p.h \
                              ./JrkerrElectronics/Posix/qextserial/qextserialenumerator.h \
                              ./JrkerrElectronics/Posix/qextserial/qextserialenumerator_p.h \
                              ./JrkerrElectronics/Posix/qextserial/qextserialport_global.h
    SOURCES                += ./JrkerrElectronics/Posix/qextserial/qextserialport.cpp \
                              ./JrkerrElectronics/Posix/qextserial/qextserialenumerator.cpp
    unix:SOURCES           += ./JrkerrElectronics/Posix/qextserial/qextserialport_unix.cpp
    unix:!macx:SOURCES     += ./JrkerrElectronics/Posix/qextserial/qextserialenumerator_unix.cpp
    macx:SOURCES           += ./JrkerrElectronics/Posix/qextserial/qextserialenumerator_osx.cpp
    win32:SOURCES          += ./JrkerrElectronics/Posix/qextserial/qextserialport_win.cpp \
                              ./JrkerrElectronics/Posix/qextserial/qextserialenumerator_win.cpp

    # For Windows user who doesn't have Qt's Private files
    win32{
        DEFINES            += QESP_NO_QT_PRIVATE
        HEADERS            += ./JrkerrElectronics/Posix/qextserial/qextwineventnotifier_p.h
        SOURCES            += ./JrkerrElectronics/Posix/qextserial/qextwineventnotifier_p.cpp
    }

macx:LIBS              += -framework IOKit -framework CoreFoundation
win32:LIBS             += -lsetupapi -ladvapi32 -luser32
