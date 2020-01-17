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

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/DbUnit/ArchiveForms

INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ModbusMasterUnit
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ScriptUnit

INCLUDEPATH += ./
INCLUDEPATH += ./Frames
INCLUDEPATH += ./Frames/Widgets
INCLUDEPATH += ./Frames/ArchiveFrames
INCLUDEPATH += ./Frames/SettingsFrames
#############################################################
HEADERS += \
    ClimateControlSystem.h \
    FrameName.h \
    Frames/AbstractArchiveFrame.h \
    Frames/AbstractFrame.h \
    Frames/ArchiveFrames/ClimateDeviceAutoArchiveFrame.h \
    Frames/ArchiveFrames/ClimateDeviceManualArchiveFrame.h \
    Frames/ArchiveFrames/ElectricalEquipmentArchiveFrame.h \
    Frames/ArchiveFrames/ElectricalEquipmentOperatingTimeArchiveFrame.h \
    Frames/ArchiveFrames/WorkTimeArchiveFrame.h \
    Frames/CarInformationFrame.h \
    Frames/InOutDisplayFrame.h \
    Frames/MainFrame.h \
    Frames/SettingsFrames/ConfigEditFrame.h \
    Frames/SettingsFrames/ItemEditSettingsWidget.h \
    Frames/SettingsFrames/MenuConfigEditFrame.h \
    Frames/SettingsFrames/NumericButton.h \
    Frames/SettingsFrames/NumericKeypadWidget.h \
    Frames/Widgets/DateTimeWidget.h \
    Frames/Widgets/DigitalStripIndicator.h \
    Frames/Widgets/GigitalIndicatorWidget.h \
    Frames/Widgets/MsgWidget.h \
    Frames/Widgets/RowMsgWidget.h \
    Frames/Widgets/StatesDisplayWidget.h \
    MainDisplayWidget.h \
    ButtonsWidget.h


SOURCES += \
    ClimateControlSystem.cpp \
    Frames/AbstractArchiveFrame.cpp \
    Frames/AbstractFrame.cpp \
    Frames/CarInformationFrame.cpp \
    Frames/InOutDisplayFrame.cpp \
    Frames/MainFrame.cpp \
    Frames/SettingsFrames/ConfigEditFrame.cpp \
    Frames/SettingsFrames/ItemEditSettingsWidget.cpp \
    Frames/SettingsFrames/MenuConfigEditFrame.cpp \
    Frames/SettingsFrames/NumericButton.cpp \
    Frames/SettingsFrames/NumericKeypadWidget.cpp \
    Frames/Widgets/DateTimeWidget.cpp \
    Frames/Widgets/DigitalStripIndicator.cpp \
    Frames/Widgets/GigitalIndicatorWidget.cpp \
    Frames/Widgets/RowMsgWidget.cpp \
    Frames/Widgets/StatesDisplayWidget.cpp \
    MainDisplayWidget.cpp \
    ButtonsWidget.cpp \
    main.cpp


FORMS += \
    Frames/CarInformationFrame.ui \
    Frames/InOutDisplayFrame.ui \
    Frames/SettingsFrames/ItemEditSettingsWidget.ui




RESOURCES += \



DISTFILES += \
    $$ROOT_PATH/bin/conf/script.json \
    $$ROOT_PATH/bin/conf/modbus.json \
    $$ROOT_PATH/bin/easylogging++.conf

#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
    -lModbusMasterUnit \
    -lScriptUnit \
    -lDbUnit \
    -leasylogging++ \



#############################################################
