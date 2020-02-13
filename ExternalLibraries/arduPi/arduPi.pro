#############################################################
# arduPi
# https://github.com/micahwalter/arduino-pi/tree/master/arduPi
#############################################################
TARGET = arduPi

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


#############################################################
HEADERS += \
    arduPi.h


SOURCES += \
    arduPi.cpp


LIBS += \
#	-lpthread
#	-lrt
