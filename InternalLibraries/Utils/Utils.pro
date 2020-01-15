#############################################################
TARGET = Utils

#############################################################
ROOT_PATH=../..

#############################################################

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################

include($$ROOT_PATH/easylogging++.pri)

#############################################################
TEMPLATE    = lib
CONFIG      += staticlib

DEPENDPATH  += ../../lib/
DESTDIR     = ../../lib/

QT -= gui
QT -= widgets

CONFIG -= app_bundle

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp/

INCLUDEPATH += ./
#############################################################
SOURCES +=


HEADERS += \
    AbstractFactory.h \
    CheckAppUniq.h \
    Log.h \
    Versions.h


FORMS += \


RESOURCES += \


OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -leasylogging++

#############################################################
