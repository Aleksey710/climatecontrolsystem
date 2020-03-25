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
QT += gui
QT += widgets
QT += sql
QT += script
#QT += scripttools


#############################################################

TEMPLATE    = app
DEPENDPATH += $$ROOT_PATH/bin/
DESTDIR     = $$ROOT_PATH/bin/

CONFIG += console

#############################################################
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/Easyloggingpp

#INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/libmodbus-3.1.3-ascii/src
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/libmodbus/modbus/libmodbus-rpi/src

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/Utils

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit/ArchiveForms

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ModbusMasterUnit
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ScriptUnit

INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/WiringPi
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/WiringPi/devLib
INCLUDEPATH += $$ROOT_PATH/ExternalLibraries/WiringPi/wiringPi


INCLUDEPATH += ./
INCLUDEPATH += ./Frames
INCLUDEPATH += ./Frames/Widgets
INCLUDEPATH += ./Frames/ArchiveFrames
INCLUDEPATH += ./Frames/SettingsFrames
#############################################################
HEADERS += \
    ButtonsControlThread.h \
    ClimateControlSystem.h \
    CpuTemperature.h \
    FrameName.h \
    Frames/AbstractArchiveFrame.h \
    Frames/AbstractFrame.h \
    Frames/ArchiveFrames/ClimateDeviceAutoArchiveFrame.h \
    Frames/ArchiveFrames/ClimateDeviceManualArchiveFrame.h \
    Frames/ArchiveFrames/ElectricalEquipmentArchiveFrame.h \
    Frames/ArchiveFrames/ElectricalEquipmentOperatingTimeArchiveFrame.h \
    Frames/ArchiveFrames/RemoveRecordsFromArchiveWidget.h \
    Frames/ArchiveFrames/WorkTimeArchiveFrame.h \
    Frames/CarInformationFrame.h \
    Frames/InOutDisplayFrame.h \
    Frames/MainFrame.h \
    Frames/SettingsFrames/ConfigEditFrame.h \
    Frames/SettingsFrames/DateTimeSetup.h \
    Frames/SettingsFrames/ItemEditSettingsWidget.h \
    Frames/SettingsFrames/MenuConfigEditFrame.h \
    Frames/SettingsFrames/NumericButton.h \
    Frames/SettingsFrames/NumericKeypadWidget.h \
    Frames/Widgets/AbstractMsgWidget.h \
    Frames/Widgets/CheckPasswordWidget.h \
    Frames/Widgets/DateTimeWidget.h \
    Frames/Widgets/DigitalStripIndicator.h \
    Frames/Widgets/GigitalIndicatorWidget.h \
    Frames/Widgets/MsgWidget.h \
    Frames/Widgets/MultiMsgWidget.h \
    Frames/Widgets/QLobel.h \
    Frames/Widgets/RowMsgWidget.h \
    Frames/Widgets/StatesDisplayWidget.h \
    MainDisplayWidget.h \
    ButtonsWidget.h \
    Password.h \
    Frames/Widgets/DataAverager.h


SOURCES += main.cpp \
    ButtonsControlThread.cpp \
    ClimateControlSystem.cpp \
    Frames/AbstractArchiveFrame.cpp \
    Frames/AbstractFrame.cpp \
    Frames/ArchiveFrames/RemoveRecordsFromArchiveWidget.cpp \
    Frames/ArchiveFrames/WorkTimeArchiveFrame.cpp \
    Frames/CarInformationFrame.cpp \
    Frames/InOutDisplayFrame.cpp \
    Frames/MainFrame.cpp \
    Frames/SettingsFrames/ConfigEditFrame.cpp \
    Frames/SettingsFrames/DateTimeSetup.cpp \
    Frames/SettingsFrames/ItemEditSettingsWidget.cpp \
    Frames/SettingsFrames/MenuConfigEditFrame.cpp \
    Frames/SettingsFrames/NumericButton.cpp \
    Frames/SettingsFrames/NumericKeypadWidget.cpp \
    Frames/Widgets/CheckPasswordWidget.cpp \
    Frames/Widgets/DateTimeWidget.cpp \
    Frames/Widgets/DigitalStripIndicator.cpp \
    Frames/Widgets/GigitalIndicatorWidget.cpp \
    Frames/Widgets/MultiMsgWidget.cpp \
    Frames/Widgets/RowMsgWidget.cpp \
    Frames/Widgets/StatesDisplayWidget.cpp \
    MainDisplayWidget.cpp \
    ButtonsWidget.cpp \
    Password.cpp \
    Frames/Widgets/DataAverager.cpp



FORMS += \
    Frames/ArchiveFrames/RemoveRecordsFromArchiveWidget.ui \
    Frames/CarInformationFrame.ui \
    Frames/InOutDisplayFrame.ui \
    Frames/SettingsFrames/DateTimeSetup.ui \
    Frames/SettingsFrames/ItemEditSettingsWidget.ui \
    Frames/Widgets/CheckPasswordWidget.ui




RESOURCES += \
    Resource.qrc



DISTFILES += \
    $$ROOT_PATH/bin/conf/script.json \
    $$ROOT_PATH/bin/conf/modbus.json \
    $$ROOT_PATH/bin/easylogging++.conf \
    images/logo_ukr.png


#############################################################
linux:LIBS += \
    -L$$ROOT_PATH/lib \
    -lWiringPi


LIBS += \
    -L$$ROOT_PATH/lib \
    -lModbusMasterUnit \
    -lScriptUnit \
    -lDbUnit \
    -leasylogging++ \
    -lmodbus \


win32|win64:LIBS += -lwsock32
win32|win64:LIBS += -lws2_32


qnx: LIBS += -lsocket

#############################################################
