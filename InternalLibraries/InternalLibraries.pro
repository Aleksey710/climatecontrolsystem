TEMPLATE = subdirs

SUBDIRS += Utils \
    AbstractDisplayWidget \
    DbUnit
SUBDIRS += AbstractConfigurator
SUBDIRS += DataModel
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
