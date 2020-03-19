#############################################################
TARGET = Imitator2

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

INCLUDEPATH += ./

CONFIG += console


SOURCES += \
    CfgReader.cpp \
    convert.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowATOR.cpp \
    modbus.cpp \
    request.cpp \
    slave.cpp


HEADERS += \
    CfgReader.h \
    convert.h \
    mainwindow.h \
    mainwindowATOR.h \
    modbus.h \
    request.h \
    serial-config.h \
    slave-data.h \
    slave.h \
#    ui_mainwindow.h \
#    ui_mainwindowATOR.h


FORMS += \
    mainwindow.ui \
    mainwindowATOR.ui


RESOURCES += \
    resources/qslave.qrc

DISTFILES += \
    LICENSE \
    README.md \
    cfg/BIU/BIU.net \
    cfg/BIU/but.xml \
    cfg/BIU/bvv.xml \
    cfg/example/example.net \
    cfg/example/traffic-light.xml \
    cfg/lastochka/brake-controller.xml \
    cfg/lastochka/lastochka.net \
    cfg/lastochka/manometer.xml \
    cfg/lastochka/panel-G.xml \
    cfg/lastochka/panel-I.xml \
    cfg/lastochka/panel-J-in.xml \
    cfg/lastochka/panel-J-out.xml \
    cfg/lastochka/panel-K.xml \
    cfg/lastochka/panel-L.xml \
    cfg/lastochka/panel-M.xml \
    cfg/lastochka/traction-controller.xml \
    cfg/lastochka/traffic-light.xml \
    resources/img/logo.ico \
    resources/img/logo.png

