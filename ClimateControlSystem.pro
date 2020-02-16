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
# https://cdn-learn.adafruit.com/downloads/pdf/adding-a-real-time-clock-to-raspberry-pi.pdf

###############################################################################
# https://github.com/stephane/libmodbus/wiki/Libmodbus-on-Raspberry-pi
# Additional notes :
#
# In order to use native RPi serial port for RTU mode, you MUST disable serial console by using
# sudo raspi-config
# as it conflicts with modes RTU communication.
#
# Native serial port is listed as ttyAMA0 under /dev/ directory.
#
# If you’re using UART to RS485 chip like 75176 or anything similar, you would like to check the libmodbus raspberry pi fork
# which makes use of a GPIO to enable rx-tx. (Link : https://github.com/dhruvvyas90/libmodbus)
#
# Known issue(s):
#
# While using RPi native UART (/dev/ttyAMA0), RPi sometimes tends to append a null byte once port has been opened and it may result into invalid reply.
# (As per this issue link : https://github.com/stephane/libmodbus/issues/302).
# You may want to use modbus_flush(ctx) after modbus_connect call just to ensure that byte is flushed.
# If problem persists, you may try OP's mothod of modifying modbus-rtu.c and recompile to make it effective.

###############################################################################
# Настройка часов реального времени
###############################################################################
# https://pimylifeup.com/raspberry-pi-rtc/
# read time directly from rtc module
# hwclock -r

# update rtc module time from system time (system time should be regularly updated by ntp from the internet if your pi is networked):
# hwclock -w

# update system time from the rtc module (this should happen on startup):
# hwclock -s

# and the most fun of all - monitor the "drift" between your system clock and the rtc module:
# hwclock -c
###############################################################################
