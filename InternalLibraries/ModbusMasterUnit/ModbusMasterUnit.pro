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

#############################################################
QT += core
QT += script
QT += sql
#------------------------------------------------------------
#MAKE_RESULT = APP
contains( MAKE_RESULT, APP ) {
    TEMPLATE    = app

    DEPENDPATH += $$ROOT_PATH/bin/
    DESTDIR     = $$ROOT_PATH/bin/

    CONFIG += console

    QT += gui
    QT += widgets
    QT += scripttools

    HEADERS  += \
        ModbusMasterUnitTestForm.h


    SOURCES += \
        main.cpp \
        ModbusMasterUnitTestForm.cpp


    FORMS += \
        ModbusMasterUnitTestForm.ui

    LIBS += \
        -L$$ROOT_PATH/lib \
        -lScriptUnit \
        -lDbUnit \
        -lmodbus \

        win32|win64:LIBS += -lwsock32
        win32|win64:LIBS += -lws2_32


        qnx:LIBS += -lsocket
}
#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp

#INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/libmodbus-3.1.3-ascii/src
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/libmodbus-rpi/src



INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ScriptUnit/

INCLUDEPATH += ./
#############################################################
SOURCES += \
    ModbusMasterHandler.cpp \
    ModbusMasterUnit.cpp \
    ModbusRequest.cpp \
    ModbusThreadController.cpp


HEADERS  += \
    ModbusConnectionSettings.h \
    ModbusMasterHandler.h \
    ModbusMasterUnit.h \
    ModbusRequest.h \
    ModbusThreadController.h



FORMS += \


RESOURCES += \


OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -leasylogging++


#############################################################

