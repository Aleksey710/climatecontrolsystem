################################
#
# easylogging++
#
################################
# https://github.com/muflihun/easyloggingpp/blob/master/samples/Qt/basic/qt-sample.pro

DEFINES += ELPP_QT_LOGGING
DEFINES += ELPP_STL_LOGGING

DEFINES += ELPP_FEATURE_ALL

#DEFINES += ELPP_ASYNC_LOGGING

# Applicable to GCC only. Enables stacktrace on application crash
DEFINES += ELPP_FEATURE_CRASH_LOG

DEFINES += ELPP_STACKTRACE_ON_CRASH

#DEFINES += ELPP_FEATURE_PERFORMANCE_TRACKING

# Enables handling SIGABRT.
# This is disabled by default to prevent annoying CTRL + C behaviour when you wish to abort.
#DEFINES += ELPP_HANDLE_SIGABRT

DEFINES += ELPP_STRICT_SIZE_CHECK
DEFINES += ELPP_UNICODE

#DEFINES += ELPP_MULTI_LOGGER_SUPPORT

# Enables thread-safety - make sure -lpthread linking for linux.
DEFINES += ELPP_THREAD_SAFE

# Forces to use C++ standard library for threading (Only useful when using ELPP_THREAD_SAFE
DEFINES += ELPP_FORCE_USE_STD_THREAD

#https://github.com/muflihun/easyloggingpp/blob/develop/samples/STL/logrotate-pthread.cpp
# для log rotate
DEFINES += ELPP_NO_DEFAULT_LOG_FILE


#QMAKE_CXXFLAGS += -std=c++11
#CONFIG += c++11

# В про
#OTHER_FILES += \
#	./bin/easylogging++.conf
