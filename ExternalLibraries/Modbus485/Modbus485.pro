#############################################################
# Modbus485
# https://www.cooking-hacks.com/documentation/tutorials/modbus-module-shield-tutorial-for-arduino-raspberry-pi-intel-galileo/
#############################################################
TARGET = Modbus485

#############################################################
ROOT_PATH=../..

include($$ROOT_PATH/ClimateControlSystem.pri)
#############################################################

include($$ROOT_PATH/easylogging++.pri)
#############################################################
MAKE_RESULT = LIB
#############################################################
TEMPLATE    = lib
CONFIG      += staticlib
DEPENDPATH  += $$ROOT_PATH/lib
DESTDIR     = $$ROOT_PATH/lib

QT -= core
QT -= gui

CONFIG += warn_off

#############################################################

CONFIG += c++11
CONFIG += console
CONFIG += app_bundle


#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/arduPi

INCLUDEPATH += ./


#############################################################
HEADERS += \
    ModbusMaster485.h \
    ModbusSlave485.h \
    RS485.h

SOURCES += \
    ModbusMaster485.cpp \
    ModbusSlave485.cpp \
    RS485.cpp \


contains( MAKE_RESULT, APP ) {
    SOURCES += \
        rs485_modbusreadcoils.cpp \
        rs485_modbusreadinputregisters.cpp \
        rs485_modbusseveralslaves.cpp \
        rs485_modbusslavemode.cpp \
        rs485_modbuswritesinglecoil.cpp \
        rs485_modbuswritesingleregister.cpp \
        rs485_receive.cpp \
        rs485_send.cpp
}

