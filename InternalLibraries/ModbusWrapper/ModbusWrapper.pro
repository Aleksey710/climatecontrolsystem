#############################################################
#
# http://libmodbus.org/download/
#

TARGET = ModbusWrapper

LIBMODBUS=libmodbus-3.1.3-ascii
#LIBMODBUS=libmodbus-3.1.4
# $$LIBMODBUS

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
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/

INCLUDEPATH += ./
#############################################################
SOURCES += \
    ModbusCore.cpp \
    ModbusASCII.cpp \
    ModbusMaster.cpp \
    ModbusSlave.cpp \
    ModbusPartner.cpp \
    ModbusRTU.cpp \
    ModbusTCP.cpp \
    ModbusSerial.cpp \
    ModbusMasterConnection.cpp \
    ModbusMasterConnectionController.cpp \
    ModbusSlaveData.cpp

HEADERS += \
    ModbusCore.h \
    ModbusConsts.h \
    ModbusASCII.h \
    ModbusMaster.h \
    ModbusSlave.h \
    ModbusPartner.h \
    ModbusRTU.h \
    ModbusTCP.h \
    ModbusSerial.h \
    ModbusRequester.h \
    ModbusData.h \
    ModbusConnectionAddress.h \
    ModbusRequest.h \
    ModbusMasterConnection.h \
    ModbusMasterConnectionController.h \
    ModbusSlaveData.h \
    ModbusType.h


FORMS += \


RESOURCES += \


OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -lmodbus \
    -leasylogging++

#############################################################
win32:LIBS += -lwsock32
win32:LIBS += -lws2_32

win64:LIBS += -lwsock32
win64:LIBS += -lws2_64

qnx:LIBS += -lsocket
