TEMPLATE = subdirs

SUBDIRS += Utils
SUBDIRS += ModbusWrapper 
SUBDIRS += ModbusMasterUnit


ModbusWrapper.depends = \
    Utils \


ModbusMasterUnit.depends = \
    ModbusWrapper \
