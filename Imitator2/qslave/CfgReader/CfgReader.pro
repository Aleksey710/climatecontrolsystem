TEMPLATE = lib

OBJECTS_DIR = ./build/$$TARGET
MOC_DIR     = ./build/$$TARGET
UI_DIR      = ./build/$$TARGET
RCC_DIR     = ./build/$$TARGET

QT -= qui
QT += xml

CONFIG += staticlib

TARGET = CfgReader

DESTDIR = ../../lib

INCLUDEPATH += ./include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
