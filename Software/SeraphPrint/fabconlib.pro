HEADERS += \
    ../FabConLib/bay.h \
    ../FabConLib/xdflpath.h \
    ../FabConLib/xdflvoxel.h \
    ../FabConLib/material.h \
    ../FabConLib/xyzmotion.h \
    ../FabConLib/xdflhandler.h \
    ../FabConLib/virtualmachines.h \
    ../FabConLib/coreinterface.h \
    ../FabConLib/loadconfigthread.h \
    ../FabConLib/jsnpath.h \
    ../FabConLib/jscmotion.h \
    ../FabConLib/jsxyz.h \
    ../FabConLib/testing/util.h \
    ../FabConLib/testing/unittests.h \
    ../FabConLib/testing/testerforci.h \
    ../FabConLib/testing/jscitest.h \
    ../FabConLib/comportdetector.h

SOURCES += \
    ../FabConLib/bay.cpp \
    ../FabConLib/xdflpath.cpp \
    ../FabConLib/xdflvoxel.cpp \
    ../FabConLib/material.cpp \
    ../FabConLib/xyzmotion.cpp \
    ../FabConLib/xdflhandler.cpp \
    ../FabConLib/virtualmachines.cpp \
    ../FabConLib/coreinterface.cpp \
    ../FabConLib/loadconfigthread.cpp \
    ../FabConLib/jsnpath.cpp \
    ../FabConLib/jscmotion.cpp \
    ../FabConLib/jsxyz.cpp \
    ../FabConLib/testing/util.cpp \
    ../FabConLib/testing/unittests.cpp \
    ../FabConLib/testing/testerforci.cpp \
    ../FabConLib/testing/jscitest.cpp \
    ../FabConLib/comportdetector.cpp



INCLUDEPATH += ../JrkerrElectronics/
include("JrKerr_Electronics.pro")

OTHER_FILES += \
    ../../media/testxdfl.xdfl \
    ../../media/TestScript.js \
    ../../media/testConfig.config \
    ../../media/testxdfl-test.xdfl \
    ../../media/testxdfl-mid.xdfl \
    ../../media/JrKerr-Valve.config \
    ../../media/JrKerr-Single-deposition.config \
    ../../media/JrKerr-Duel-deposition.config

