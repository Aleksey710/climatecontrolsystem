#############################################################
TARGET = ModbusMasterUnit

#############################################################

LIBMODBUS=libmodbus-3.1.3-ascii
#LIBMODBUS=libmodbus-3.1.4
# $$LIBMODBUS

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


#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/qmqtt/qmqtt/mqtt
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src/isi

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ModbusWrapper/

INCLUDEPATH += ./
#############################################################
SOURCES += \
    ModbusMasterUnit.cpp \
    ModbusDeviceItem.cpp \
    ModbusRegisterItem.cpp \
    AbstractModbusItem.cpp \
    ModbusConnectionItem.cpp \
    ModbusSerialConnectionItem.cpp \
    ModbusTcpConnectionItem.cpp \
    ModbusMasterConfigurator.cpp



HEADERS  += \
    ModbusMasterUnit.h \
    ModbusDeviceItem.h \
    ModbusRegisterItem.h \
    AbstractModbusItem.h \
    ModbusConnectionItem.h \
    ModbusTcpConnectionItem.h \
    ModbusSerialConnectionItem.h \
    ModbusMasterConfigurator.h



FORMS += \




RESOURCES += \


OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lModbusWrapper \
    -lLog \
    -lmodbus \
    -leasylogging++


#############################################################
win32:LIBS += -lwsock32
win32:LIBS += -lws2_32

win64:LIBS += -lwsock32
win64:LIBS += -lws2_64

qnx:LIBS += -lsocket


