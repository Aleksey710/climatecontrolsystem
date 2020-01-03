TEMPLATE = subdirs

SUBDIRS += Utils
SUBDIRS += DbUnit
SUBDIRS += ScriptUnit
SUBDIRS += ModbusMasterUnit

DbUnit.depends = \
    Utils \


ScriptUnit.depends = \
    Utils \
    DbUnit


ModbusMasterUnit.depends = \
    Utils \
    DbUnit \
    ScriptUnit



