TEMPLATE = subdirs

SUBDIRS += Utils
SUBDIRS += DataModel
SUBDIRS += AbstractConfigurator
SUBDIRS += ModbusWrapper 
SUBDIRS += ModbusMasterUnit


DataModel.depends = \
    Utils \


AbstractConfigurator.depends = \
    Utils \
    DataModel \


ModbusWrapper.depends = \
    Utils \


ModbusMasterUnit.depends = \
    Utils \
    DataModel \
    AbstractConfigurator
