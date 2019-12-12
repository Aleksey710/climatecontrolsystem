#ifndef EASYLOGGINGCUSTOM_H
#define EASYLOGGINGCUSTOM_H
//------------------------------------------------------------------------------------
#include <unistd.h> // for sleep()
#include <pthread.h>
#include <thread>
#include <mutex>

#include <QDir>
#include <QString>
#include <QDateTime>
#include <QCoreApplication>


//------------------------------------------------------------------------------------
// #include "easyloggingCustom.h"

#define LOG_ROTATE_PERIOD_HOURS 1
//------------------------------------------------------------------------------------
//void* logRotate(void*);

//! My crash handler
void myCrashHandler(int sig);

void easyloggingInit(int argc, char *argv[]);
//------------------------------------------------------------------------------------
#endif // EASYLOGGINGCUSTOM_H
