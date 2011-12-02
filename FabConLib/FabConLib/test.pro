# -------------------------------------------------
# Project created by QtCreator 2011-06-10T00:48:58
# -------------------------------------------------
DEFINES += CONFIRM_ENABLED
QT += script \
    xml
#TARGET = TestMotors
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += FabConLib/FabConLib/jsnpath.cpp \
    FabConLib/FabConLib/bay.cpp \
    FabConLib/FabConLib/xdflpath.cpp \
    FabConLib/FabConLib/xdflvoxel.cpp \
    FabConLib/FabConLib/material.cpp \
    FabConLib/FabConLib/xyzmotion.cpp \
    FabConLib/FabConLib/jscmotion.cpp \
    FabConLib/FabConLib/jsxyz.cpp \
    FabConLib/FabConLib/util.cpp \
    FabConLib/FabConLib/xdflhandler.cpp \
    FabConLib/FabConLib/unittests.cpp \
    FabConLib/FabConLib/virtualmachines.cpp
HEADERS += \
    FabConLib/FabConLib/jsnpath.h \
    FabConLib/FabConLib/bay.h \
    FabConLib/FabConLib/xdflpath.h \
    FabConLib/FabConLib/xdflvoxel.h \
    FabConLib/FabConLib/material.h \
    FabConLib/FabConLib/xyzmotion.h \
    FabConLib/FabConLib/jscmotion.h \
    FabConLib/FabConLib/jsxyz.h \
    FabConLib/FabConLib/util.h \
    FabConLib/FabConLib/xdflhandler.h \
    FabConLib/FabConLib/unittests.h \
    FabConLib/FabConLib/virtualmachines.h
INCLUDEPATH += JrkerrElectronics/
include("JrKerr_Electronics.pro")
OTHER_FILES += \
    media/testxdfl.xdfl \
    media/TestScript.js \
    media/testConfig.config \
    media/testxdfl-test.xdfl \
    media/testxdfl-mid.xdfl






















