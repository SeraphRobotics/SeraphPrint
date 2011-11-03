#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T13:56:22
#
#-------------------------------------------------

QT       += core gui

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
    gamepad.cpp

HEADERS  += mainwindow.h \
        connectwidget.h \
        jobwidget.h \
        printwidget.h \
        baydialog.h \
        baywidget.h \
        materialswidget.h \
    gamepad.h

FORMS    += mainwindow.ui \
        connectwidget.ui \
        jobwidget.ui \
        printwidget.ui \
        baydialog.ui \
        baywidget.ui \
        materialswidget.ui \
    gamepad.ui

INCLUDEPATH += FabInterpreter
include(FabInterpreter/Interpreter.pro)

RESOURCES +=














