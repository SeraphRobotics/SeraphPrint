DEPENDPATH += ./Common/Posix/JrKerr
INCLUDEPATH += ./Common/Posix/JrKerr/src
#QMAKE_LIBDIR += ./Common/JrKerr/src/build

HEADERS += ./Common/Posix/JrKerr/nmccom.h \
    ./Common/Posix/JrKerr/picio.h \
    ./Common/Posix/JrKerr/picservo.h\
    ./Common/Posix/JrKerr/picstep.h \
    ./Common/Posix/JrKerr/path.h

SOURCES += ./Common/Posix/JrKerr/nmccom.cpp \
    ./Common/Posix/JrKerr/picio.cpp \
    ./Common/Posix/JrKerr/picservo.cpp\
    ./Common/Posix/JrKerr/picstep.cpp \
    ./Common/Posix/JrKerr/path.cpp

#CONFIG(debug, debug|release):LIBS += -lqextserialportd
#else:LIBS += -lqextserialport
