TEMPLATE = subdirs
  
SUBDIRS += ExternalLibraries
SUBDIRS += InternalLibraries
SUBDIRS += ClimateControlSystem

#SUBDIRS += Imitator

#contains(TARGET_ARCH, __arm__): SUBDIRS += Imitator
#host_build {
#    QT_ARCH = x86_64
#    QT_TARGET_ARCH = arm
#} else {
#    QT_ARCH = arm
#}

!contains(QMAKE_HOST.arch, __arm__):{
    message("Not ARM platform")
    SUBDIRS += Imitator
}

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

# Настройка времени
#https://cdn-learn.adafruit.com/downloads/pdf/adding-a-real-time-clock-to-raspberry-pi.pdf

