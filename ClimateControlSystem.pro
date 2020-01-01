TEMPLATE = subdirs

SUBDIRS += ExternalLibraries
SUBDIRS += InternalLibraries
SUBDIRS += ClimateControlSystem


InternalLibraries.depends = \
    ExternalLibraries \


ClimateControlSystem.depends = \
    InternalLibraries \

# sudo apt install qtscript5-dev

# sudo apt install \
# libqt5script5 \
# libqt5serialport5 \
# libqt5serialbus5 \
# libqt5sql5-sqlite \

HEADERS += \
    ClimateControlSystem/Frames/Widgets/AbstractDisplayWidget.h

SOURCES += \
    ClimateControlSystem/Frames/Widgets/AbstractDisplayWidget.cpp

CONFIG += qt

QT += widgets



