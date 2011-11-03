DEPENDPATH += ./Common/Windows/JrKerr
INCLUDEPATH += ./Common/Windows/JrKerr/src
#QMAKE_LIBDIR += ./Common/JrKerr/src/build

HEADERS += ./Common/Windows/JrKerr/nmccom.h \
    ./Common/Windows/JrKerr/picservo.h\
    ./Common/Windows/JrKerr/path.h

#CONFIG(debug, debug|release):LIBS += -lqextserialportd
#else:LIBS += -lqextserialport
