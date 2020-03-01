TEMPLATE = subdirs


SUBDIRS += Easyloggingpp 

SUBDIRS += libmodbus

linux:SUBDIRS += WiringPi

#SUBDIRS += arduPi
#SUBDIRS += Modbus485

#Modbus485.depends = \
#    arduPi
