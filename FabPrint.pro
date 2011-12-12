#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T13:56:22
#
#-------------------------------------------------

QT       += core gui\
          xml\
          script

TARGET = FabPrint
TEMPLATE = app

SOURCES += main.cpp\
        connectwidget.cpp \
        jobwidget.cpp \
        printwidget.cpp \
        baydialog.cpp \
        baywidget.cpp \
        materialswidget.cpp \
        mainwindow.cpp \
    gamepad.cpp \
    motordialog.cpp

HEADERS  += mainwindow.h \
        connectwidget.h \
        jobwidget.h \
        printwidget.h \
        baydialog.h \
        baywidget.h \
        materialswidget.h \
    gamepad.h \
    motordialog.h

FORMS    += mainwindow.ui \
        connectwidget.ui \
        jobwidget.ui \
        printwidget.ui \
        baydialog.ui \
        baywidget.ui \
        materialswidget.ui \
    gamepad.ui \
    motordialog.ui

INCLUDEPATH += FabConLib
include(FabConLib/FabConLib/include.pro)

RESOURCES += \
    arrows/resources.qrc
