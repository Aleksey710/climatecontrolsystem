#include "CustomFunctions.h"

//------------------------------------------------------------------------------------
QScriptValue redefinedScriptPrint(QScriptContext *context, QScriptEngine *engine)
{
    QString result;
    for (int i = 0; i < context->argumentCount(); ++i)
    {
        if (i > 0)
        {
            result.append(" ");
        }

        QScriptValue scriptValue = context->argument(i);

        QString resultPart = scriptValue.toString();

        result.append(resultPart);
    }

    //QScriptValue calleeData = context->callee().data();

    SEND_TO_LOG( QString("scriptPrint: %2").arg( result ) );

    return engine->undefinedValue();
}
//------------------------------------------------------------------------------------
//!
QScriptValue regToFloat(QScriptContext *context, QScriptEngine *engine)
{
    quint16 r0 = context->argument(0).toUInt16();
    quint16 r1 = context->argument(1).toUInt16();

    //SEND_TO_LOG( QString("RegToFloat(%1, %2)").arg(r0).arg(r1) );

    float value = regToFloatWorker(r0, r1);

    return engine->newVariant( value );
}
//------------------------------------------------------------------------------------
//!
float regToFloatWorker(const quint16 &r0, const quint16 &r1)
{
    union {
        uint32_t v32;
        float   vf;
    } data;

    //!------------------------------
    data.v32 = uint32_t(r0 << 16);
    data.v32 = data.v32 | r1;

    //!------------------------------
    //! Обработка отключения устройства
    if(data.vf < float(0.01) )
        data.vf = 0;

    //!------------------------------
    //! округление до сотых
    data.vf = (uint32_t(data.vf*100 + float(0.5)))/float(100.0);

    //!------------------------------
    /*
        SEND_TO_LOG( QString("regToFloat(%1, %2) "
                             //"{%3, %4, %5, %6} "
                             "= %3")
                     .arg(r0).arg(r1)
                     //.arg(r[0]).arg(r[1]).arg(r[2]).arg(r[3])
                     .arg(*vf));
    */

    return data.vf;
}
//------------------------------------------------------------------------------------
//!
std::function<void(const int &msgId,
                   const double &value)> ArchiveFunction;
//------------------------------------------------------------------------------------
//!
void archiveWorker(const int &msgId, const double &value)
{
    if(ArchiveFunction)
    {
        ArchiveFunction(msgId, value);
    }

    //SEND_TO_LOG( QString("CustomFunctions.cpp archiveWorker %1 %2").arg(msgId).arg(value));
}
//------------------------------------------------------------------------------------
//!
QScriptValue archive(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(engine);

    int msgId = context->argument(0).toInt32();
    double value = context->argument(1).toNumber();

    //SEND_TO_LOG( QString("archive(%1, %2)").arg(msgId).arg(value) );

    archiveWorker(msgId, value);

    return QScriptValue();
}
