
# event driven device enumeration on windows requires the gui module
#!win32:QT               -= gui

#OBJECTS_DIR             += ./Common/JrKerr/tmp
#MOC_DIR                 += ./Common/JrKerr/tmp
DEPENDDIR              += ./Common/Posix/JrKerr/src/
INCLUDEDIR             += ./Common/Posix/JrKerr/src/ ./Common/Posix/JrKerr/tmp
HEADERS                 += ./Common/Posix/JrKerr/src/qextserialport.h \
                          ./Common/Posix/JrKerr/src/qextserialenumerator.h \
                          ./Common/Posix/JrKerr/src/qextserialport_global.h
SOURCES                 += ./Common/Posix/JrKerr/src/qextserialport.cpp

unix:SOURCES           += ./Common/Posix/JrKerr/src/posix_qextserialport.cpp
unix:!macx:SOURCES     += ./Common/Posix/JrKerr/src/qextserialenumerator_unix.cpp
macx {
  SOURCES          += ./Common/Posix/JrKerr/src/qextserialenumerator_osx.cpp
  LIBS             += -framework IOKit -framework CoreFoundation
}

win32 {
  SOURCES          += ./Common/Posix/JrKerr/src/win_qextserialport.cpp ./Common/Posix/JrKerr/src/qextserialenumerator_win.cpp
  DEFINES          += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
  LIBS             += -lsetupapi
}
