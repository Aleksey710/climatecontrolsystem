#ROOT_PATH = ../..

# -----------------------------------------------------------
OBJECTS_DIR = $$ROOT_PATH/build/$$TARGET
MOC_DIR     = $$ROOT_PATH/build/$$TARGET
UI_DIR      = $$ROOT_PATH/build/$$TARGET
RCC_DIR     = $$ROOT_PATH/build/$$TARGET

# -----------------------------------------------------------
LIBS += -L$$ROOT_PATH/lib \

#############################################################
if ( contains( CONFIG, USE_CCACHE ) ) {

    QMAKE_CC    = ccache gcc
    QMAKE_CXX   = ccache g++

} else {

    QMAKE_CC  = gcc
    QMAKE_CXX = g++
}

#############################################################
CONFIG += c++11
#CONFIG += c++14
#CONFIG += c++17

#QMAKE_CXXFLAGS += -std=c++11
#QMAKE_CXXFLAGS += -std=gnu++11

CONFIG += qt
CONFIG += warn_on
CONFIG += silent
#CONFIG += thread
CONFIG += console
#------------------------------------------------------------------------------
#CONFIG += cmdline
CONFIG += precompile_header

# Use Precompiled headers (PCH)
#PRECOMPILED_HEADER  = $$ROOT_PATH/stable.h

precompile_header:!isEmpty(PRECOMPILED_HEADER) {
    DEFINES += USING_PCH
}
#------------------------------------------------------------------------------
#Application version
DEFINES += VERSION_MAJOR=0
DEFINES += VERSION_MINOR=1
DEFINES += VERSION_BUILD=1

#------------------------------------------------------------------------------
# OS
#message( $$QMAKE_HOST.arch )                 # Host architecture
#message( $$QMAKE_HOST.os )                   # Host OS
#message( $$QMAKE_HOST.cpu_count )            # Number of available cpus
#message( $$QMAKE_HOST.name )                 # Host computer name
#message( $$QMAKE_HOST.version )              # Host OS version number
#message( $$QMAKE_HOST.version_string )       # Host OS version string

DEFINES += QMAKE_HOST_os='\\"$${QMAKE_HOST.os}\\"'
DEFINES += QMAKE_HOST_arch='\\"$${QMAKE_HOST.arch}\\"'
DEFINES += QMAKE_HOST_version='\\"$${QMAKE_HOST.version}\\"'

#------------------------------------------------------------------------------
unix:DISTRIBUTION1  = $$system(cat /etc/issue | cut -d\' \' -f1)
unix:DISTRIBUTION2  = $$system(cat /etc/issue | cut -d\' \' -f2)
unix:DISTRIBUTION3  = $$system(cat /etc/issue | cut -d\' \' -f3)
unix:DISTRIBUTION4  = $$system(cat /etc/issue | cut -d\' \' -f4)

DEFINES += DISTRIBUTION1='\\"$${DISTRIBUTION1}\\"'
DEFINES += DISTRIBUTION2='\\"$${DISTRIBUTION2}\\"'
DEFINES += DISTRIBUTION3='\\"$${DISTRIBUTION3}\\"'
DEFINES += DISTRIBUTION4='\\"$${DISTRIBUTION4}\\"'

#------------------------------------------------------------------------------
unix:DATE_CREATED = $$system(date +"%d-%m-%Y")
unix:TIME_CREATED = $$system(date +"%H:%M")

DEFINES += DATE_CREATED='\\"$${DATE_CREATED}\\"'
DEFINES += TIME_CREATED='\\"$${TIME_CREATED}\\"'

#------------------------------------------------------------------------------
QMAKE_TARGET_COPYRIGHT = (c) PanasenkoA
