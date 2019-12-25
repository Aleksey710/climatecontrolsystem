#############################################################
TARGET = DbUnit

#############################################################
ROOT_PATH=../..

#############################################################

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################

include($$ROOT_PATH/easylogging++.pri)

#############################################################
#TEMPLATE    = lib
#CONFIG      += staticlib

#DEPENDPATH  = $$ROOT_PATH/lib
#DESTDIR     = $$ROOT_PATH/lib

#------------------------------------------------------------
TEMPLATE    = app
DEPENDPATH += $$ROOT_PATH/bin/
DESTDIR     = $$ROOT_PATH/bin/

CONFIG += console

SOURCES += main.cpp \
    ConfigEditForm.cpp

#############################################################
QT += gui
QT += widgets
QT += core
QT += sql

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/


INCLUDEPATH += ./
#############################################################

HEADERS += \
    ConfigEditForm.h \
    DbUnit.h

SOURCES += \
    DbUnit.cpp




FORMS += \
    ConfigEditForm.ui



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -leasylogging++


#############################################################
