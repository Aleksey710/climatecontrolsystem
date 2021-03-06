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
#MAKE_RESULT = APP
contains( MAKE_RESULT, APP ) {
    #TEMPLATE    = app
    #DEPENDPATH += $$ROOT_PATH/bin/
    #DESTDIR     = $$ROOT_PATH/bin/

    #CONFIG += console

    #SOURCES += main.cpp
}
#############################################################
QT -= gui
QT -= widgets
QT += core
QT += sql

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils/


INCLUDEPATH += ./
INCLUDEPATH += ./ArchiveForms
#############################################################

HEADERS += \
    ArchiveJournalType.h \
    ArchiveMsg.h \
    DbUnit.h \
    MenuItemData.h \
    ArchiveWriter.h


SOURCES += \
    DbUnit.cpp \
    ArchiveWriter.cpp


FORMS +=



RESOURCES += \



OTHER_FILES += \


#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lUtils \
    -leasylogging++


#############################################################
