#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H
//------------------------------------------------------------------------------------
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptValue>
#include <stdlib.h>

#include <bitset>

#if defined(_WIN32) //ntohl
# include <winsock2.h>
#else
# include <arpa/inet.h>
#endif

#include "Log.h"
//------------------------------------------------------------------------------------
// #include "CustomFunctions.h"
//------------------------------------------------------------------------------------

QScriptValue redefinedScriptPrint(QScriptContext *context, QScriptEngine *engine);

QScriptValue getRandomColor(QScriptContext *context, QScriptEngine *engine);

//------------------------------------------------------------------------------------
//float regToFloat3210Worker(const quint16 &r0, const quint16 &r1);

//QScriptValue regToFloat3210(QScriptContext *context, QScriptEngine *engine);
//------------------------------------------------------------------------------------

float RegToFloatWorker(const quint16 &r0, const quint16 &r1);
//! RegToFloat(reg0, reg1);
QScriptValue RegToFloat(QScriptContext *context, QScriptEngine *engine);


//------------------------------------------------------------------------------------
#endif // CUSTOMFUNCTIONS_H
