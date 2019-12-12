#############################################################
#
# http://libmodbus.org/download/
#
#
# добавлен Modbus ASCII
#
# https://github.com/stephane/libmodbus/pull/111/commits/8f996ab83ebcb09de390345528b690b48047c2f4
#

TARGET = modbus

##############################################################################
LIBMODBUS=libmodbus-3.1.3-ascii
#LIBMODBUS=libmodbus-3.1.4


#############################################################
ROOT_PATH=../../..

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################
TEMPLATE    = lib
CONFIG      += staticlib
DEPENDPATH  += $$ROOT_PATH/lib/
DESTDIR     = $$ROOT_PATH/lib/

QT += core
QT -= gui

CONFIG -= app_bundle

CONFIG += warn_off

#############################################################

INCLUDEPATH += ./$$LIBMODBUS
INCLUDEPATH += ./$$LIBMODBUS/src

#############################################################
SOURCES += \
    $$LIBMODBUS/src/modbus.c \
    $$LIBMODBUS/src/modbus-data.c \
    $$LIBMODBUS/src/modbus-rtu.c \
    $$LIBMODBUS/src/modbus-tcp.c \
    $$LIBMODBUS/src/modbus-ascii.c \


HEADERS += \
    $$LIBMODBUS/config.h \
    $$LIBMODBUS/src/modbus-version.h \
#    $$LIBMODBUS/src/modbus-version.h.in
    $$LIBMODBUS/src/modbus.h \
    $$LIBMODBUS/src/modbus-private.h \
    $$LIBMODBUS/src/modbus-rtu.h \
    $$LIBMODBUS/src/modbus-rtu-private.h \
    $$LIBMODBUS/src/modbus-tcp.h \
    $$LIBMODBUS/src/modbus-tcp-private.h \
    $$LIBMODBUS/src/modbus-ascii.h \
    $$LIBMODBUS/src/modbus-ascii-private.h \
    libmodbus-3.1.3-ascii/src/modbus-log.h

#############################################################


contains( LIBMODBUS, libmodbus-3.1.3-ascii ) {
    HEADERS += \
        $$LIBMODBUS/src/modbus-serial.h
        $$LIBMODBUS/src/modbus-serial-private.h

    SOURCES += \
        $$LIBMODBUS/src/modbus-serial.c
}


FORMS += \


RESOURCES += \


OTHER_FILES += \


#############################################################

win32|win64:LIBS += -lwsock32
win32|win64:LIBS += -lws2_32


qnx:LIBS += -lsocket
