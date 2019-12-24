#############################################################
TARGET = ModbusMasterUnit

#############################################################
ROOT_PATH=../..

#############################################################

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################

include($$ROOT_PATH/easylogging++.pri)

#############################################################
TEMPLATE    = lib
CONFIG      += staticlib

DEPENDPATH  += $$ROOT_PATH/lib
DESTDIR     = $$ROOT_PATH/lib

QT -= gui
QT += core
QT += network
QT += serialbus
QT += serialport


#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/qmqtt/qmqtt/mqtt
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src/isi

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/AbstractConfigurator
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DataModel/

INCLUDEPATH += ./
#############################################################
SOURCES += \
    ModbusConnectionInterrogator.cpp \
    ModbusMasterHandler.cpp \
    ModbusMasterUnit.cpp \
    ModbusMasterConfigurator.cpp



HEADERS  += \
    ModbusConnection.h \
    ModbusConnectionController.h \
    ModbusConnectionInterrogator.h \
    ModbusConnectionSettings.h \
    ModbusMasterHandler.h \
    ModbusMasterUnit.h \
    ModbusMasterConfigurator.h



FORMS += \




RESOURCES += \


OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lDataModel \
    -lAbstractConfigurator \
    -lUtils \
    -lmodbus \
    -leasylogging++


#############################################################

