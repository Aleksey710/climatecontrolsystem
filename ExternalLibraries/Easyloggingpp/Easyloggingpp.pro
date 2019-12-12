#############################################################
# Easylogging++ v9.96.7
#############################################################
TARGET = easylogging++

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

QT += core
QT -= gui

CONFIG += warn_off

#############################################################

CONFIG += c++11
CONFIG += console
CONFIG += app_bundle

#############################################################
SOURCES += \
    easylogging++.cc \
    easyloggingCustom.cpp


HEADERS += \
    easylogging++.h \
    easyloggingCustom.h


LIBS += \
    -lz \

