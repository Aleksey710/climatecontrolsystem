#!/bin/bash

DATE=$(date+"%Y.%m.%d.%H:%M:%S")
#echo -e "n\DATE - 1" >> /home/pi/climatecontrolsystem/bin/start.log

# Отключить Wifi
#sudo ifconfig wlan0 down

# Убрать рабочий стол
# killall lxpanel

DATE=$(date+"%Y.%m.%d.%H:%M:%S")
#echo -e "n\DATE - 2" >> /home/pi/climatecontrolsystem/bin/start.log

cd /home/pi/climatecontrolsystem/bin

DATE=$(date+"%Y.%m.%d.%H:%M:%S")
#echo -e "n\DATE - 3" >> /home/pi/climatecontrolsystem/bin/start.log

./ClimateControlSystem


DATE=$(date+"%Y.%m.%d.%H:%M:%S")
#echo -e "n\DATE - 4" >> /home/pi/climatecontrolsystem/bin/start.log

