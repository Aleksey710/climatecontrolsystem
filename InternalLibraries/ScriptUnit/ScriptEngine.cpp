#include "ScriptEngine.h"

//------------------------------------------------------------------------------------
//!
ScriptEngine::ScriptEngine(QObject *parent)
             :QScriptEngine(parent)
{
    setObjectName(QString("ScriptEngine"));
    SEND_TO_LOG( QString("%1 - создание и инициализация скриптового обработчика (%2)")
          .arg(objectName()).arg( (quint64)thread() ) );

    appendCommon();

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - скриптовый обработчик создан и инициализирован (%2)")
          .arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
ScriptEngine::~ScriptEngine()
{
    SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
void ScriptEngine::appendCommon()
{
    //------------------------------------------------------------------------------------
    //qml
    //installExtensions(QJSEngine::TranslationExtension | QJSEngine::ConsoleExtension);
    //------------------------------------------------------------------------------------
    QScriptValue redefinedScriptPrint_sv = newFunction( redefinedScriptPrint );
    globalObject().setProperty("print", redefinedScriptPrint_sv);

    QScriptValue regToFloat_sv = newFunction( regToFloat );
    globalObject().setProperty("regToFloat", regToFloat_sv);

    QScriptValue archive_sv = newFunction( archive );
    globalObject().setProperty("archive", archive_sv);

    QScriptValue saveSettings_sv = newFunction( saveSettings );
    globalObject().setProperty("saveSettings", saveSettings_sv);

    QScriptValue saveStringSettings_sv = newFunction( saveStringSettings );
    globalObject().setProperty("saveStringSettings", saveStringSettings_sv);

    QScriptValue setCoolerMode_sv = newFunction( setCoolerMode );
    globalObject().setProperty("setCoolerMode", setCoolerMode_sv);

    QScriptValue getCpuT_sv = newFunction( getCpuT );
    globalObject().setProperty("getCpuT", getCpuT_sv);

    QScriptValue systemShutdown_sv = newFunction( systemShutdown );
    globalObject().setProperty("systemShutdown", systemShutdown_sv);


    //------------------------------------------------------------------------------------
    SEND_TO_LOG( QString("%1 - стандартные функции добавлены").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void ScriptEngine::evaluate(const QString &scriptText,
                            QObject* obj,
                            const char *member
                            )
{
    //SEND_TO_LOG( QString("%1 - evaluate [%2]").arg(objectName()).arg( scriptText ) );

    if (obj && member)
    {
        QScriptValue scriptValue = QScriptEngine::evaluate(scriptText);

        if(hasUncaughtException())
        {
            SEND_TO_LOG( QString("%1 - evaluate uncaughtExceptionLineNumber [%2] \n"
                                 "%3\n"
                                 "%4\n")
                         .arg(objectName())
                         .arg(uncaughtExceptionLineNumber())
                         .arg(uncaughtExceptionBacktrace().join(" "))
                         .arg(scriptText)
                         );
        }

        QMetaObject::invokeMethod(obj,
                                  member,
                                  Qt::QueuedConnection,
                                  //Qt::DirectConnection,
                                  Q_ARG(QScriptValue, scriptValue));
    } else {
        QScriptEngine::evaluate(scriptText);

        if(hasUncaughtException())
        {
            SEND_TO_LOG( QString("%1 - evaluate uncaughtExceptionLineNumber [%2] \n"
                                 "%3\n"
                                 "%4\n")
                         .arg(objectName())
                         .arg(uncaughtExceptionLineNumber())
                         .arg(uncaughtExceptionBacktrace().join(" "))
                         .arg(scriptText)
                         );
        }

        //SEND_TO_LOG( QString("%1 - evaluate result [%2]").arg(objectName()).arg( scriptValue.toString() ) );
    }
}
//------------------------------------------------------------------------------------
//!
void ScriptEngine::addGlobalQbject(QObject *obj)
{
    QScriptValue scriptValue = newQObject(obj);

    globalObject().setProperty(obj->objectName(), scriptValue);

    //printAllObject(scriptValue);
}
//------------------------------------------------------------------------------------
//!
void ScriptEngine::printAllObject(const QScriptValue &scriptValue)
{
    QScriptValueIterator it(scriptValue);
    while (it.hasNext())
    {
        it.next();
        qDebug() << "Метод [" << it.name() << "] - значение[" << it.value().toString()<< "]";
    }

//            QScriptValue obj = scriptValue; // the object to iterate over
//            while (obj.isObject())
//            {
//                QScriptValueIterator it(obj);
//                while (it.hasNext())
//                {
//                    it.next();
//                    qDebug() << "Метод :" << it.name();
//                }
//                obj = obj.prototype();
//            }
}
//------------------------------------------------------------------------------------
//!

