#!/bin/sh

cd /home/pi/climatecontrolsystem

git pull
qmake
make -j2