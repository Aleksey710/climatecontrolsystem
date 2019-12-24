#############################################################
TARGET = AbstractDisplayWidget

#############################################################
ROOT_PATH=../..

#############################################################

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################

include($$ROOT_PATH/easylogging++.pri)

#############################################################
TEMPLATE    = lib
CONFIG      += staticlib

DEPENDPATH  = $$ROOT_PATH/lib
DESTDIR     = $$ROOT_PATH/lib
QT += gui
QT += widgets
QT += core

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/


INCLUDEPATH += ./
#############################################################

SOURCES += \
#    main.cpp \
    AbstractDisplayWidget.cpp

HEADERS += \
    AbstractDisplayWidget.h

FORMS += \
    AbstractDisplayWidget.ui



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -leasylogging++


#############################################################
