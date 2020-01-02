#############################################################
TARGET = ScriptUnit

#############################################################
ROOT_PATH=../..

#############################################################

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################

include($$ROOT_PATH/easylogging++.pri)

#############################################################
TEMPLATE    = lib
CONFIG      += staticlib

DEPENDPATH  = $$ROOT_PATH/lib
DESTDIR     = $$ROOT_PATH/lib

#------------------------------------------------------------
#TEMPLATE    = app
#DEPENDPATH += $$ROOT_PATH/bin/
#DESTDIR     = $$ROOT_PATH/bin/

#CONFIG += console

#SOURCES += main.cpp
#############################################################
QT += core
QT += gui
QT += widgets
QT += sql
QT += script
QT += scripttools
#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/


INCLUDEPATH += ./
INCLUDEPATH += ./DataSources
INCLUDEPATH += ./View
#############################################################

HEADERS += \
    CustomFunctions.h \
    DataSources/DataSourceScriptObject.h \
    ScriptEngine.h \
    ScriptObject.h \
    ScriptUnit.h \
    View/RegisterDataProcessingForm.h \
    View/ScriptHighlighter.h


SOURCES += \
    DataSources/DataSourceScriptObject.cpp \
    ScriptUnit.cpp \
    CustomFunctions.cpp \
    ScriptEngine.cpp \
    View/RegisterDataProcessingForm.cpp \
    View/ScriptHighlighter.cpp






FORMS += \
    View/RegisterDataProcessingForm.ui



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -leasylogging++


#############################################################
