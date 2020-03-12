TEMPLATE = lib

OBJECTS_DIR = ./build/$$TARGET
MOC_DIR     = ./build/$$TARGET
UI_DIR      = ./build/$$TARGET
RCC_DIR     = ./build/$$TARGET

TARGET = modbus

QT += core serialport

CONFIG += staticlib

DESTDIR = ../../lib

INCLUDEPATH = ./include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
