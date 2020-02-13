#############################################################
#
# http://libmodbus.org/download/
#
#
# добавлен Modbus ASCII
#
# https://github.com/stephane/libmodbus/pull/111/commits/8f996ab83ebcb09de390345528b690b48047c2f4
#
# For RPi
# https://github.com/dhruvvyas90/libmodbus

TARGET = modbus

#LIBMODBUS=libmodbus-3.1.3-ascii
LIBMODBUS=libmodbus-rpi

#############################################################
ROOT_PATH=../../..

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################
MAKE_RESULT = LIB
############################################################
# Для библиотеки
contains( MAKE_RESULT, LIB ) {
    #message(--- MAKE_RESULT - LIB!!! ---)

    TEMPLATE    = lib
    CONFIG      += staticlib
    #CONFIG      += sharedlib build_all
    #CONFIG      += shared_and_static #build_all
    DEPENDPATH  += $$ROOT_PATH/lib/
    DESTDIR     = $$ROOT_PATH/lib/

    QT -= core
    QT -= gui

    CONFIG -= app_bundle
    #CONFIG   += dll

    CONFIG += warn_off
}
#############################################################

#############################################################

INCLUDEPATH += ./$$LIBMODBUS
INCLUDEPATH += ./$$LIBMODBUS/src

#############################################################
SOURCES += \
    $$LIBMODBUS/src/modbus.c \
    $$LIBMODBUS/src/modbus-data.c \
    $$LIBMODBUS/src/modbus-rtu.c \
    $$LIBMODBUS/src/modbus-tcp.c \
    


HEADERS += \
    $$LIBMODBUS/config.h \
    $$LIBMODBUS/src/modbus-version.h \
    $$LIBMODBUS/src/modbus.h \
    $$LIBMODBUS/src/modbus-private.h \
    $$LIBMODBUS/src/modbus-rtu.h \
    $$LIBMODBUS/src/modbus-rtu-private.h \
    $$LIBMODBUS/src/modbus-tcp.h \
    $$LIBMODBUS/src/modbus-tcp-private.h \


#############################################################


contains( LIBMODBUS, libmodbus-3.1.3-ascii ) {
    HEADERS += \
        $$LIBMODBUS/src/modbus-serial.h \
        $$LIBMODBUS/src/modbus-serial-private.h \
        $$LIBMODBUS/src/modbus-ascii.h \
        $$LIBMODBUS/src/modbus-ascii-private.h \
        $$LIBMODBUS/src/modbus-log.h


    SOURCES += \
        $$LIBMODBUS/src/modbus-serial.c \
        $$LIBMODBUS/src/modbus-ascii.c \
}


FORMS += \


RESOURCES += \


OTHER_FILES += \


#############################################################

win32|win64:LIBS += -lwsock32
win32|win64:LIBS += -lws2_32


qnx:LIBS += -lsocket
