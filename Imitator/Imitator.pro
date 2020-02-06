#############################################################
TARGET = Imitator

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

QT += serialbus
QT += widgets
#requires(qtConfig(combobox))
QT += serialport

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    mainwindowATOR.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    mainwindowATOR.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    mainwindowATOR.ui

RESOURCES += slave.qrc

