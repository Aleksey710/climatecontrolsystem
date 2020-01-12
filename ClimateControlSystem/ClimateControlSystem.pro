#############################################################
TARGET = ClimateControlSystem

#############################################################
ROOT_PATH=..

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
INCLUDEPATH += ./Frames/Widgets
#############################################################
HEADERS += \
    ClimateControlSystem.h \
    Frames/AbstractFrames.h \
    Frames/CarInformationFrame.h \
    Frames/InOutDisplayFrame.h \
    Frames/MainFrame.h \
    Frames/Widgets/DateTimeWidget.h \
    Frames/Widgets/DigitalStripIndicator.h \
    Frames/Widgets/GigitalIndicatorWidget.h \
    Frames/Widgets/MsgWidget.h \
    Frames/Widgets/RowMsgWidget.h \
    Frames/Widgets/StatesDisplayWidget.h \
    MainDisplayWidget.h \


SOURCES += \
    ClimateControlSystem.cpp \
    Frames/AbstractFrames.cpp \
    Frames/CarInformationFrame.cpp \
    Frames/InOutDisplayFrame.cpp \
    Frames/MainFrame.cpp \
    Frames/Widgets/DateTimeWidget.cpp \
    Frames/Widgets/DigitalStripIndicator.cpp \
    Frames/Widgets/GigitalIndicatorWidget.cpp \
    Frames/Widgets/RowMsgWidget.cpp \
    Frames/Widgets/StatesDisplayWidget.cpp \
    MainDisplayWidget.cpp \
    main.cpp


FORMS += \
    Frames/CarInformationFrame.ui \
    Frames/InOutDisplayFrame.ui




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
    -leasylogging++ \



#############################################################
