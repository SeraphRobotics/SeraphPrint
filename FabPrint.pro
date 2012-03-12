#-------------------------------------------------
#
# Project created by QtCreator 2011-10-24T13:56:22
#
#-------------------------------------------------

QT += \
    core \
    gui \
    xml \
    script

TARGET = SeraphPrint
TEMPLATE = app

SOURCES += \
    main.cpp \
    connectwidget.cpp \
    jobwidget.cpp \
    printwidget.cpp \
    baydialog.cpp \
    baywidget.cpp \
    materialswidget.cpp \
    mainwindow.cpp \
    gamepad.cpp \
    motordialog.cpp \
    aboutdialog.cpp

HEADERS += \
    mainwindow.h \
    connectwidget.h \
    jobwidget.h \
    printwidget.h \
    baydialog.h \
    baywidget.h \
    materialswidget.h \
    gamepad.h \
    motordialog.h \
    aboutdialog.h

FORMS += \
    mainwindow.ui \
    connectwidget.ui \
    jobwidget.ui \
    printwidget.ui \
    baydialog.ui \
    baywidget.ui \
    materialswidget.ui \
    gamepad.ui \
    motordialog.ui \
    aboutdialog.ui

INCLUDEPATH += FabConLib
include(FabConLib/FabConLib/include.pro)

RESOURCES += fabprint.qrc
//OTHER_FILES += fabstudio.rc
RC_FILE = fabstudio.rc

# OTHER_FILES should be referenced in include.pro.
