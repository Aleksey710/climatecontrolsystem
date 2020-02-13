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

DEFINES += NATIVE_MODBUS_HANDLER

#############################################################
TEMPLATE    = lib
CONFIG      += staticlib

DEPENDPATH  += $$ROOT_PATH/lib
DESTDIR     = $$ROOT_PATH/lib
#------------------------------------------------------------
#MAKE_RESULT = APP
contains( MAKE_RESULT, APP ) {
    TEMPLATE    = app

    DEPENDPATH += $$ROOT_PATH/bin/
    DESTDIR     = $$ROOT_PATH/bin/

    CONFIG += console

    HEADERS  += \
        ModbusMasterUnitTestForm.h


    SOURCES += \
        main.cpp \
        ModbusMasterUnitTestForm.cpp


    FORMS += \
        ModbusMasterUnitTestForm.ui

    LIBS += \
        -L$$ROOT_PATH/lib \
        -lmodbus \

        win32|win64:LIBS += -lwsock32
        win32|win64:LIBS += -lws2_32


        qnx:LIBS += -lsocket
}
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

INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/arduPi

INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Modbus485

#INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/libmodbus-3.1.3-ascii/src
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/libmodbus-rpi/src



INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ScriptUnit/

INCLUDEPATH += ./
#############################################################
SOURCES += \
    AbstractModbusMasterHandler.cpp \
    LibmodbusModbusMasterHandler.cpp \
    ModbusMasterHandler.cpp \
#    ModbusMaster485Handler.cpp \
    ModbusMasterUnit.cpp \
    ModbusRequest.cpp \
    NativeModbusMasterHandler.cpp



HEADERS  += \
    AbstractModbusMasterHandler.h \
    LibmodbusModbusMasterHandler.h \
    ModbusConnection.h \
    ModbusConnectionSettings.h \
    ModbusMasterHandler.h \
#    ModbusMaster485Handler.h \
    ModbusMasterUnit.h \
    NativeModbusMasterHandler.h \
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


#unix:LIBS += \
#    -L$$ROOT_PATH/lib \
#    -lWiringPi \
#    -lModbus485 \
#    -larduPi \


#LIBS += \
#    -lpthread \
#    -lrt


#win32|win64:LIBS += -lwsock32
#win32|win64:LIBS += -lws2_32


#qnx:LIBS += -lsocket
#############################################################

