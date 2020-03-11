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
# Настройка заставки
# https://raspberry-projects.com/pi/pi-operating-systems/raspbian/custom-boot-up-screen
# sudo apt-get install fbi
#
# Replace the file /usr/share/plymouth/themes/pix/splash.png with your own (or just remove it for a blank screen)

# Add logo.nologo to the end of the line in /boot/cmdline.txt to remove the four raspberries (on pi3)
###############################################################################
# настройка яркости и гаммы
# sudo apt install xcalib
# sudo apt install xbacklight
# https://xakep.ru/2017/06/14/linux-powersaving/
# https://booss.org/reducing-screen-brightness-at-night-on-linux-with-xcalib/
###############################################################################
# Сенсорный экран
# https://www.waveshare.com/w/upload/5/56/PWM_control_backlight_manual.pdf
# https://www.waveshare.com/wiki/7inch_HDMI_LCD_(B)
###############################################################################
# Часто не требуется использовать графическую оболочку в Linux
# Теперь правильнее отключать графическую оболочку в systemd.
#
# Для отключения вводим команду:
# systemctl set-default multi-user.target
#
# Для включения обратно:
# systemctl set-default graphical.target
#
# посмотреть текущее состояние:
# systemctl get-default
#
# Если в ответе будет graphical.target, то графическая оболочка включена и multi-user.target, если выключена.
###############################################################################
# https://www.cryptoprofi.info/?p=4949
# Display Manager - /usr/sbin/lightdm
# Посмотреть какой DM используется можно так:
# cat /etc/X11/default-display-manager
#
# Если графическая оболочка не удалена из системы, то в нее можно перейти, выполнив команду:
# sudo /etc/init.d/lightdm start
#
# Удалить DM
# update-rc.d -f используемый-DM remove
#
# Вернуть всё на место:
# update-rc.d -f используемый-DM defaults
###############################################################################
# https://losst.ru/nastrojka-linghtdm-v-linux
###############################################################################
# lubuntu-desktop xubuntu-desktop kubuntu-desktop mate-desktop cinnamon-desktop
# apt list --installed | grep desktop
# https://www.geeks3d.com/hacklab/20160108/how-to-disable-the-blank-screen-on-raspberry-pi-raspbian/
# https://www.element14.com/community/community/raspberry-pi/raspberrypi2/blog/2015/04/08/setting-up-an-xfce-desktop-environment-on-pi
# https://help.ubuntu.ru/wiki/lightdm  ЯРКОСТЬ
#
#
#

