#############################################################
TARGET = AbstractConfigurator

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

#SOURCES += main.cpp
#############################################################
QT -= gui
QT -= widget
QT += core

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/


INCLUDEPATH += ./
#############################################################

SOURCES += \
    AbstractConfigurator.cpp \


HEADERS += \
    AbstractConfigurator.h


FORMS += \



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -leasylogging++


#############################################################
