#############################################################
TARGET = ModbusMasterUnit

#############################################################
ROOT_PATH=../..

#############################################################

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################

include($$ROOT_PATH/easylogging++.pri)

#############################################################
DEFINES += CIRCULAR_PROCESSING_REQUEST

#############################################################
TEMPLATE    = lib
CONFIG      += staticlib

DEPENDPATH  += $$ROOT_PATH/lib
DESTDIR     = $$ROOT_PATH/lib
#------------------------------------------------------------
TEMPLATE    = app
DEPENDPATH += $$ROOT_PATH/bin/
DESTDIR     = $$ROOT_PATH/bin/

CONFIG += console

SOURCES += main.cpp

#############################################################
QT += gui
QT += widgets
QT += core
QT += network
QT += serialbus
QT += serialport
QT += sql
QT += script
QT += scripttools

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/qmqtt/qmqtt/mqtt
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src/isi

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ScriptUnit/

INCLUDEPATH += ./
#############################################################
SOURCES += \
    ModbusMasterHandler.cpp \
    ModbusMasterUnit.cpp \
    ModbusRequest.cpp



HEADERS  += \
    ModbusConnection.h \
    ModbusConnectionController.h \
    ModbusConnectionSettings.h \
    ModbusMasterHandler.h \
    ModbusMasterUnit.h \
    ModbusRequest.h



FORMS += \




RESOURCES += \


OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lScriptUnit \
    -lDbUnit \
    -lUtils \
    -leasylogging++


#############################################################

