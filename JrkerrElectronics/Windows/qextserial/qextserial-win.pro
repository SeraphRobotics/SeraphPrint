SOURCES  += qextserialenumerator.cpp\
            qextserialport_win.cpp \
            qextserialenumerator_win.cpp\
            qextserialport.cpp


HEADERS  += qextserialport.h \
            qextserialport_p.h \
            qextserialenumerator.h \
            qextserialenumerator_p.h \
            qextserialport_global.h



# For Windows user who doesn't have Qt's Private files
win32:!exists($$[QT_INSTALL_HEADERS]/QtCore/private/qwineventnotifier_p.h){
        DEFINES            += QESP_NO_QT_PRIVATE
        HEADERS            += qextwineventnotifier_p.h
        SOURCES            += qextwineventnotifier_p.cpp
}
win32:LIBS             += -lsetupapi -ladvapi32 -luser32
