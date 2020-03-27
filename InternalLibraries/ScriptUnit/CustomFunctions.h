#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H
//------------------------------------------------------------------------------------
/*
#if defined(_WIN32) //ntohl
# include <winsock2.h>
#else
# include <arpa/inet.h>
#endif
*/
//
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptValue>
#include <QTimer>

#include <stdlib.h>
#include <functional>

#include <bitset>
#include <QProcess>


#include "Log.h"
//------------------------------------------------------------------------------------
// #include "CustomFunctions.h"
//------------------------------------------------------------------------------------

QScriptValue redefinedScriptPrint(QScriptContext *context, QScriptEngine *engine);
//------------------------------------
float regToFloatWorker(const quint16 &r0, const quint16 &r1);
//! RegToFloat(reg0, reg1);
QScriptValue regToFloat(QScriptContext *context, QScriptEngine *engine);

//------------------------------------
// Записать в архив сообщение по типу
extern std::function<void(const int &, const double &)> ArchiveFunction;

void archiveWorker(const int &msgId, const double &value);
QScriptValue archive(QScriptContext *context, QScriptEngine *engine);

//------------------------------------
// Сохранение числовых значений
extern std::function<void(const QString &, const QString &, const double &)> SaveSettingsFunction;

void saveSettingsWorker(const QString &groupe, const QString &param, const double &value);
QScriptValue saveSettings(QScriptContext *context, QScriptEngine *engine);
//------------------------------------
// Сохранение строковых значений
extern std::function<void(const QString &, const QString &, const QString &)> SaveStringSettingsFunction;

void saveStringSettingsWorker(const QString &groupe, const QString &param, const QString &value);
QScriptValue saveStringSettings(QScriptContext *context, QScriptEngine *engine);

//------------------------------------
// Включить/Выключить вентилятор обдува
extern std::function<void(const bool &)> SetCoolerModeFunction;

void setCoolerModeWorker(const bool &value);
QScriptValue setCoolerMode(QScriptContext *context, QScriptEngine *engine);

//------------------------------------
// Задать яркость экрана
extern std::function<void(const int &)> SetScreenBrightness;

void setScreenBrightnessWorker(const int &value);
QScriptValue setScreenBrightness(QScriptContext *context, QScriptEngine *engine);

//------------------------------------
// Получить температуру процессора
extern std::function<float()> getCpuTFunction;

float getCpuTWorker();
QScriptValue getCpuT(QScriptContext *context, QScriptEngine *engine);

//------------------------------------
// Функция нормального завершения работы
QScriptValue systemShutdown(QScriptContext *context, QScriptEngine *engine);
//------------------------------------------------------------------------------------
#endif // CUSTOMFUNCTIONS_H
