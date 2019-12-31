TEMPLATE = subdirs

SUBDIRS += Utils
SUBDIRS += AbstractDisplayWidget
SUBDIRS += DataModel
SUBDIRS += DbUnit
SUBDIRS += ScriptUnit
SUBDIRS += AbstractConfigurator
#SUBDIRS += ModbusWrapper
SUBDIRS += ModbusMasterUnit



AbstractConfigurator.depends = \
    Utils \


DataModel.depends = \
    Utils \
    AbstractConfigurator \


#ModbusWrapper.depends = \
#    Utils \


ModbusMasterUnit.depends = \
    Utils \
    DataModel \
    AbstractConfigurator


ScriptUnit.depends = \
    Utils \
    DataModel \
