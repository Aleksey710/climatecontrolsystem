#!/bin/sh

#-------------------------------------------------------------------------
#https://cdn-learn.adafruit.com/downloads/pdf/adding-a-real-time-clock-to-raspberry-pi.pdf

#-------------------------------------------------------------------------
# Disable the "fake hwclock" which interferes with the 'real' hwclock
sudo apt-get -y remove fake-hwclock
sudo update-rc.d -f fake-hwclock remove
sudo systemctl disable fake-hwclock

#-------------------------------------------------------------------------
# Run sudo nano /lib/udev/hwclock-set and comment out these three lines:
# if [ -e /run/systemd/system ] ; then
#  exit 0
# fi

# Also comment out the two lines
# /sbin/hwclock --rtc=$dev --systz --badyear
# and
# /sbin/hwclock --rtc=$dev --systz
#-------------------------------------------------------------------------

sudo hwclock -D -r






