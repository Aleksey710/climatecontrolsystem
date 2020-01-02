TEMPLATE = subdirs

SUBDIRS += Utils
#SUBDIRS += AbstractDisplayWidget
SUBDIRS += DbUnit
SUBDIRS += ScriptUnit
#SUBDIRS += ModbusWrapper
SUBDIRS += ModbusMasterUnit

DbUnit.depends = \
    Utils \


ScriptUnit.depends = \
    Utils \


#ModbusWrapper.depends = \
#    Utils \


ModbusMasterUnit.depends = \
    Utils \



