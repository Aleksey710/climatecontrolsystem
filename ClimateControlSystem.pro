TEMPLATE = subdirs

SUBDIRS += ExternalLibraries 
SUBDIRS += ClimateControlSystem


ClimateControlSystem.depends = \
    ExternalLibraries \
