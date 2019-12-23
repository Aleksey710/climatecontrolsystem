#############################################################
TARGET = DataModel

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


#TEMPLATE    = app
#DEPENDPATH += $$ROOT_PATH/bin/
#DESTDIR     = $$ROOT_PATH/bin/



QT -= gui
QT -= widgets
QT += core


#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/AbstractConfigurator/


INCLUDEPATH += ./
#############################################################

SOURCES += \
    main.cpp \
    DataItem.cpp \
    DataModel.cpp \
    DataModelConfigurator.cpp


HEADERS += \
    DataItem.h \
    DataModel.h \
    DataModelConfigurator.h



FORMS += \



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lAbstractConfigurator \
    -lUtils \
    -leasylogging++


#############################################################

