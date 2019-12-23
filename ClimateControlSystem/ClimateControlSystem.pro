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
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/AbstractConfigurator
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ModbusWrapper
INCLUDEPATH += $$ROOT_PATH/InternalLibraries/ModbusMasterUnit

INCLUDEPATH += ./
#############################################################

SOURCES += \
    ClimateControlSystem.cpp \
    MainDisplayWidget.cpp \
    main.cpp


HEADERS += \
    ClimateControlSystem.h \
    MainDisplayWidget.h \


FORMS +=


RESOURCES += \



OTHER_FILES += \



DISTFILES += \
    $$ROOT_PATH/bin/easylogging++.conf

#############################################################
LIBS += \
    -L$$ROOT_PATH/lib \
#    -lModbusMasterUnit \
    -lDataModel \
    -lAbstractConfigurator \
#    -lUtils \
#    -lmodbus \
    -leasylogging++ \



#############################################################
