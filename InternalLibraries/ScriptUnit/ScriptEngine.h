#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H
//------------------------------------------------------------------------------------
// Qt Script
#include <QScriptEngine>
// http://doc.qt.io/qt-5/qtscript-index.html
// http://doc.crossplatform.ru/qt/4.6.x/scripting.html
//------------------------------------------------------------------------------------
// QJSEngine Class
// QT += qml
// #include <QJSEngine>
// http://doc.qt.io/qt-5/qjsengine.html
// QJSEngine       *m_engine;
//------------------------------------------------------------------------------------
#include <QObject>
#include <QScriptValueIterator>
#include <QScriptValue>
#include <QScriptContext>
//qml
//#include <QJSEngine>
//#include <>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "CustomFunctions.h"
//------------------------------------------------------------------------------------
#define USE_SCRIPT_ENGINE_DEBUGGER
//------------------------------------------------------------------------------------
//!
class ScriptEngine : public QScriptEngine
{
        Q_OBJECT
    public:
        explicit ScriptEngine(QObject *parent = Q_NULLPTR);
        virtual ~ScriptEngine();

    signals:


    public slots:
        void evaluate(const QString &scriptText,
                      QObject* obj = Q_NULLPTR,
                      const char *member = Q_NULLPTR
                      );

        Q_INVOKABLE void addGlobalQbject(QObject *obj);

    private:
        void appendCommon();
        void printAllObject(const QScriptValue &scriptValue);

    private:


};
//------------------------------------------------------------------------------------
#endif // SCRIPTENGINE_H
