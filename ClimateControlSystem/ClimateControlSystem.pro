#############################################################
TARGET = ClimateControlSystem

#############################################################
ROOT_PATH=..

LIBMODBUS=libmodbus-3.1.3-ascii
#LIBMODBUS=libmodbus-3.1.4
# $$LIBMODBUS

#############################################################

include($$ROOT_PATH/ClimateControlSystem.pri)

#############################################################

include($$ROOT_PATH/easylogging++.pri)

#############################################################
QT += core
QT += network
QT += gui
QT += widgets
QT += xml
QT += sql
QT += serialbus
QT += serialport
QT += script
QT += scripttools


#############################################################

TEMPLATE    = app
DEPENDPATH += $$ROOT_PATH/bin/
DESTDIR     = $$ROOT_PATH/bin/

CONFIG += console

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/$$LIBMODBUS/src

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DataModel

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit/ArchiveForms

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/AbstractConfigurator
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ModbusWrapper
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ModbusMasterUnit
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ScriptUnit

INCLUDEPATH += ./
INCLUDEPATH += ./Frames
#############################################################

SOURCES += \
    ClimateControlSystem.cpp \
    Frames/AbstractFrames.cpp \
    Frames/CarInformationFrame.cpp \
    Frames/InOutDisplayFrame.cpp \
    Frames/MainFrame.cpp \
    Frames/Widgets/AbstractDisplayWidget.cpp \
    MainDisplayWidget.cpp \
    main.cpp


HEADERS += \
    ClimateControlSystem.h \
    Frames/AbstractFrames.h \
    Frames/CarInformationFrame.h \
    Frames/InOutDisplayFrame.h \
    Frames/MainFrame.h \
    Frames/Widgets/AbstractDisplayWidget.h \
    MainDisplayWidget.h \


FORMS += \
    Frames/CarInformationFrame.ui \
    Frames/InOutDisplayFrame.ui \
    Frames/MainFrame.ui




RESOURCES += \



OTHER_FILES += \



DISTFILES += \
    $$ROOT_PATH/bin/easylogging++.conf

#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lModbusMasterUnit \
    -lScriptUnit \
    -lDbUnit \
#    -lDataModel \
#    -lAbstractConfigurator \
#    -lUtils \
#    -lmodbus \
    -leasylogging++ \



#############################################################
