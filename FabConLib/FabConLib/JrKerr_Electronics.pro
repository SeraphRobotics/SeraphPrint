# -------------------------------------------------
# Project created by QtCreator 2011-06-10T00:48:58
# -------------------------------------------------
SOURCES += JrkerrElectronics/electronicsinterface.cpp \
    JrkerrElectronics/motor.cpp \
    JrkerrElectronics/coordinatedmotion.cpp \
    JrkerrElectronics/npath.cpp \
    JrkerrElectronics/nmotion.cpp
HEADERS += JrkerrElectronics/electronicsinterface.h \
    JrkerrElectronics/motor.h \
    JrkerrElectronics/coordinatedmotion.h \
    JrkerrElectronics/npath.h \
    JrkerrElectronics/nmotion.h


win32: {
    INCLUDEPATH += JrkerrElectronics/Windows/
    include("win-src.pro")
    include("qextserial-src.pro")
}
unix: {
    INCLUDEPATH += JrkerrElectronics/Posix/
    include("posix-src.pro")
    include("qextserial-src.pro")
}





