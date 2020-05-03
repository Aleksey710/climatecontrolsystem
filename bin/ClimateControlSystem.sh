#!/bin/bash

DATE=$(date+"%Y.%m.%d.%H:%M:%S")
#echo -e "n\DATE - 1" >> /home/pi/climatecontrolsystem/bin/start.log

# Отключить Wifi
#sudo ifconfig wlan0 down

# Убрать рабочий стол
# killall lxpanel


sudo hwclock -s --verbose 

cd /home/pi/climatecontrolsystem/bin

./ClimateControlSystem
