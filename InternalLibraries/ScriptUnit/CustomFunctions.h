#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H
//------------------------------------------------------------------------------------
#if defined(_WIN32) //ntohl
# include <winsock2.h>
#else
# include <arpa/inet.h>
#endif
//
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptValue>
#include <stdlib.h>
#include <functional>

#include <bitset>



#include "Log.h"
//------------------------------------------------------------------------------------
// #include "CustomFunctions.h"
//------------------------------------------------------------------------------------

QScriptValue redefinedScriptPrint(QScriptContext *context, QScriptEngine *engine);

float regToFloatWorker(const quint16 &r0, const quint16 &r1);
//! RegToFloat(reg0, reg1);
QScriptValue regToFloat(QScriptContext *context, QScriptEngine *engine);


extern std::function<void(const int &msgId,
                          const double &value)> ArchiveFunction;

void archiveWorker(const int &msgId, const double &value);
QScriptValue archive(QScriptContext *context, QScriptEngine *engine);

//------------------------------------------------------------------------------------
#endif // CUSTOMFUNCTIONS_H
