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
QT -= gui
QT -= widget
QT += core

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/qmqtt/qmqtt/mqtt
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src/isi

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/


INCLUDEPATH += ./
#############################################################

SOURCES += \
    AbstractConfigurator.cpp


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
