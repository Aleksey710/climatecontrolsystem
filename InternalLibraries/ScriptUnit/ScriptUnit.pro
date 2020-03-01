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

QT -= gui
QT -= widgets

DEPENDPATH  = $$ROOT_PATH/lib
DESTDIR     = $$ROOT_PATH/lib

#------------------------------------------------------------
#MAKE_RESULT = APP
#contains( MAKE_RESULT, APP ) {
#    TEMPLATE    = app
#    DEPENDPATH += $$ROOT_PATH/bin/
#    DESTDIR     = $$ROOT_PATH/bin/

#    QT += gui
#    QT += widgets

#    CONFIG += console

#    HEADERS += \
#        View/RegisterDataProcessingForm.h \
#        View/ScriptHighlighter.h

#    SOURCES += \
#        main.cpp \
#        View/RegisterDataProcessingForm.cpp \
#        View/ScriptHighlighter.cpp

#    FORMS += \
#        View/RegisterDataProcessingForm.ui
#}
#############################################################
QT += core
QT += sql
QT += script
QT += scripttools
#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit/ArchiveForms

INCLUDEPATH += ./
INCLUDEPATH += ./View
#############################################################

HEADERS += \
    CurentTimeScriptObject.h \
    CustomFunctions.h \
    ScriptEngine.h \
    ScriptObject.h \
    ScriptUnit.h \


SOURCES += \
    ScriptObject.cpp \
    ScriptUnit.cpp \
    CustomFunctions.cpp \
    ScriptEngine.cpp \


FORMS += \



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lDbUnit \
    -lUtils \
    -leasylogging++


#############################################################
