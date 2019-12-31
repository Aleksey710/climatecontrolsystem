#############################################################
TARGET = DbUnit

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

#------------------------------------------------------------
#TEMPLATE    = app
#DEPENDPATH += $$ROOT_PATH/bin/
#DESTDIR     = $$ROOT_PATH/bin/

#CONFIG += console

#SOURCES += main.cpp



#############################################################
QT += gui
QT += widgets
QT += core
QT += sql

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/


INCLUDEPATH += ./
#############################################################

HEADERS += \
    ConfigEditFrame.h \
    DbUnit.h \
    MenuConfigEditForm.h \
    MenuItemData.h \
    NumericButton.h \
    NumericKeypadWidget.h

SOURCES += \
    DbUnit.cpp \
    NumericButton.cpp \
    NumericKeypadWidget.cpp \
    MenuConfigEditForm.cpp \
    ConfigEditFrame.cpp



FORMS +=



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -leasylogging++


#############################################################
