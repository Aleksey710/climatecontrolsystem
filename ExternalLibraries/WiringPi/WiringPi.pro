#############################################################
# WiringPi
#############################################################
TARGET = WiringPi

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
INCLUDEPATH += ./
INCLUDEPATH += ./devLib
INCLUDEPATH += ./wiringPi

#############################################################
SOURCES += \
    devLib/ds1302.c \
    devLib/gertboard.c \
    devLib/lcd.c \
    devLib/lcd128x64.c \
    devLib/maxdetect.c \
    devLib/piFace.c \
    devLib/piFaceOld.c \
    devLib/piGlow.c \
    devLib/piNes.c \
    devLib/scrollPhat.c \
    wiringPi/ads1115.c \
    wiringPi/bmp180.c \
    wiringPi/drcNet.c \
    wiringPi/drcSerial.c \
    wiringPi/ds18b20.c \
    wiringPi/htu21d.c \
    wiringPi/max31855.c \
    wiringPi/max5322.c \
    wiringPi/mcp23008.c \
    wiringPi/mcp23016.c \
    wiringPi/mcp23017.c \
    wiringPi/mcp23s08.c \
    wiringPi/mcp23s17.c \
    wiringPi/mcp3002.c \
    wiringPi/mcp3004.c \
    wiringPi/mcp3422.c \
    wiringPi/mcp4802.c \
    wiringPi/pcf8574.c \
    wiringPi/pcf8591.c \
    wiringPi/piHiPri.c \
    wiringPi/piThread.c \
    wiringPi/pseudoPins.c \
    wiringPi/rht03.c \
    wiringPi/sn3218.c \
    wiringPi/softPwm.c \
    wiringPi/softServo.c \
    wiringPi/softTone.c \
    wiringPi/sr595.c \
    wiringPi/wiringPi.c \
    wiringPi/wiringPiI2C.c \
    wiringPi/wiringPiSPI.c \
    wiringPi/wiringSerial.c \
    wiringPi/wiringShift.c \
    wiringPi/wpiExtensions.c


HEADERS += \
    devLib/ds1302.h \
    devLib/font.h \
    devLib/gertboard.h \
    devLib/lcd.h \
    devLib/lcd128x64.h \
    devLib/maxdetect.h \
    devLib/piFace.h \
    devLib/piGlow.h \
    devLib/piNes.h \
    devLib/scrollPhat.h \
    devLib/scrollPhatFont.h \
    version.h \
    wiringPi/ads1115.h \
    wiringPi/bmp180.h \
    wiringPi/drcNet.h \
    wiringPi/drcSerial.h \
    wiringPi/ds18b20.h \
    wiringPi/htu21d.h \
    wiringPi/max31855.h \
    wiringPi/max5322.h \
    wiringPi/mcp23008.h \
    wiringPi/mcp23016.h \
    wiringPi/mcp23016reg.h \
    wiringPi/mcp23017.h \
    wiringPi/mcp23s08.h \
    wiringPi/mcp23s17.h \
    wiringPi/mcp23x08.h \
    wiringPi/mcp23x0817.h \
    wiringPi/mcp3002.h \
    wiringPi/mcp3004.h \
    wiringPi/mcp3422.h \
    wiringPi/mcp4802.h \
    wiringPi/pcf8574.h \
    wiringPi/pcf8591.h \
    wiringPi/pseudoPins.h \
    wiringPi/rht03.h \
    wiringPi/sn3218.h \
    wiringPi/softPwm.h \
    wiringPi/softServo.h \
    wiringPi/softTone.h \
    wiringPi/sr595.h \
    wiringPi/wiringPi.h \
    wiringPi/wiringPiI2C.h \
    wiringPi/wiringPiSPI.h \
    wiringPi/wiringSerial.h \
    wiringPi/wiringShift.h \
    wiringPi/wpiExtensions.h


LIBS += \

DISTFILES += \
    COPYING.LESSER \
    README.md \
    VERSION \
    wiringPi/COPYING.LESSER \
    wiringPi/noMoreStatic

