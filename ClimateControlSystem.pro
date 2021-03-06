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
#    linux:SUBDIRS += Imitator
#    linux:SUBDIRS += Imitator2
}

InternalLibraries.depends = \
    ExternalLibraries \


ClimateControlSystem.depends = \
    InternalLibraries \

###############################################################################
# sudo apt install qtscript5-dev

# sudo apt install \
# libqt5script5 \
# libqt5serialport5 \
# libqt5serialbus5 \
# libqt5sql5-sqlite \
# pmount \
#
###############################################################################
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
# sudo hwclock -r

# update rtc module time from system time (system time should be regularly updated by ntp from the internet if your pi is networked):
# sudo hwclock -w

# update system time from the rtc module (this should happen on startup):
# sudo hwclock -s

# and the most fun of all - monitor the "drift" between your system clock and the rtc module:
# sudo hwclock -c

# Прописать время в RTC
# sudo hwclock --set --date="2020-04-20 12:40:05"
# Время из RTC
# sudo hwclock
#
#sudo hwclock --set --date="2011-04-17 16:45:05 ; sudo hwclock -s
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
#
# Задать яркость (рабочий диапазон 450 - 510)
# gpio -g pwm 18 1024
# gpio -g mode 18 pwm
# gpio pwmc 1000
# gpio -g pwm 18 %1
#
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
#
###############################################################################
# как отключить скринсейвер
# /home/pi/.config/lxsession/LXDE/autostart
# убрать #@xscreensaver -no-splash
#
###############################################################################
# Запустить рабочий стол
# killall lxpanel
# lxpanel
#
#/etc/xdg/lxsession/LXDE-pi/autostart
# Закоментировать все:
# @lxpanel --profile LXDE-pi
# @pcmanfm --desktop --profile LXDE-pi
# @xscreensaver -no-splash
#
###############################################################################
# Отключение lxpanel - отключает автомонтирование флэшек

###############################################################################
# https://losst.ru/nastrojka-linghtdm-v-linux
#
###############################################################################
# lubuntu-desktop xubuntu-desktop kubuntu-desktop mate-desktop cinnamon-desktop
# apt list --installed | grep desktop
# https://www.geeks3d.com/hacklab/20160108/how-to-disable-the-blank-screen-on-raspberry-pi-raspbian/
# https://www.element14.com/community/community/raspberry-pi/raspberrypi2/blog/2015/04/08/setting-up-an-xfce-desktop-environment-on-pi
# https://help.ubuntu.ru/wiki/lightdm  ЯРКОСТЬ
#
###############################################################################
# Пособия на тему...
# https://4pda.ru/forum/index.php?showtopic=308317&st=11000
#
###############################################################################
# Комбинации горячих кнопок
# QKeySequence("Ctrl+E")        - меню настроек
#    QKeySequence("Ctrl+s")     - экспорт арахива(сохранить в файл)
#    QKeySequence("Ctrl+r")     - очистить архив
# QKeySequence("Ctrl+L")        - меню яркости
#
###############################################################################
# Отключить WiFi
#sudo ifconfig wlan0 down
#sudo ifconfig wlan0 up
###############################################################################
# Рабочий метод - убирает загрузочные сообщения при загрузке
# https://scribles.net/customizing-boot-up-screen-on-raspberry-pi/
# Remove text message under splash image:
# Open “/usr/share/plymouth/themes/pix/pix.script” as root.

# sudo nano /usr/share/plymouth/themes/pix/pix.script
# Then, remove (or comment out) four lines below:
# message_sprite = Sprite();
# message_sprite.SetPosition(screen_width * 0.1, screen_height * 0.9, 10000);
#      my_image = Image.Text(text, 1, 1, 1);
#       message_sprite.SetImage(my_image);
#Note : This is a quick and dirty method I found. It works, but there might be better way.

#Remove Boot Messages
#Open “/boot/cmdline.txt” as root.
#sudo nano /boot/cmdline.txt
#Then, replace “console=tty1” with “console=tty3”. This redirects boot messages to tty3.

#Remove other things
#Still in “/boot/cmdline.txt”, add below at the end of the line

#splash quiet plymouth.ignore-serial-consoles logo.nologo vt.global_cursor_default=0
#Here are brief explanations.
#‘splash’ : enables splash image
#‘quiet’ : disable boot message texts
#‘plymouth.ignore-serial-consoles’ : not sure about this but seems it’s required when use Plymouth.
#‘logo.nologo’ : removes Raspberry Pi logo in top left corner.
#‘vt.global_cursor_default=0’ : removes blinking cursor.

#Note : The first three should be there by default, but make sure if those exist.

#Replace Splash Image
#Now, everything unwanted images and texts are gone. Let’s replace the default splash image (/usr/share/plymouth/themes/pix/splash.png) with your own splash image.

#sudo cp ~/my_splash.png /usr/share/plymouth/themes/pix/splash.png
#Note : As described in above assumption, “my_splash.png” should be your new splash image.

###############################################################################
# /boot/cmdline.txt
# console=tty3 root=PARTUUID=d9b3f436-02 rootfstype=ext4 elevator=deadline fsck.repair=yes rootwait loglevel=0 quiet splash plymouth.ignore-serial-consoles$




###############################################################################














