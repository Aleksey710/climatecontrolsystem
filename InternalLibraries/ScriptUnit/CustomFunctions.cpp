#include "CustomFunctions.h"


//---------------------------------------------------------
/*
struct byte {
    unsigned bit0: 1;
    unsigned bit1: 1;
    unsigned bit2: 1;
    unsigned bit3: 1;
    unsigned bit4: 1;
    unsigned bit5: 1;
    unsigned bit6: 1;
    unsigned bit7: 1;
};

union Register32 {
    struct {
        unsigned char byte0;
        unsigned char byte1;
        unsigned char byte2;
        unsigned char byte3;
    } charBytes;
    struct {
        byte byte0;
        byte byte1;
        byte byte2;
        byte byte3;
    } bytes;
    struct {
        uint16_t low;
        uint16_t high;
    } words;
    uint32_t dword;
    float    fl;
};
*/
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
QScriptValue getRandomColor(QScriptContext *context, QScriptEngine *engine)
{
    Q_UNUSED(context);

//    "function getRandomColor() { "
//        "var letters = '0123456789ABCDEF'; "
//        "var color = '#'; "
//        "for (var i = 0; i < 6; i++ ) "
//        "{ "
//            "color += letters[Math.floor(Math.random() * 16)]; "
//        "} "
//        "return color; "
//    "} "

    SEND_TO_LOG( QString("getRandomColor()") );

    return engine->undefinedValue();
}
//------------------------------------------------------------------------------------
//!
//QScriptValue regToFloat3210(QScriptContext *context, QScriptEngine *engine)
//{
//    quint16 r0 = context->argument(0).toUInt16();
//    quint16 r1 = context->argument(1).toUInt16();

//    //SEND_TO_LOG( QString("RegToFloat(%1, %2)").arg(r0).arg(r1) );

//    float value = RegToFloatWorker(r0, r1);

//    return engine->newVariant( value );
//}
//------------------------------------------------------------------------------------
//!
//float regToFloat3210Worker(const quint16 &r0, const quint16 &r1)
//{
//    uint32_t v32;

//    float    f;
//    float*   pf;

//    pf = &f;
//    //---------------------------------------------------------
//    v32 = uint32_t(r0) << 16;
//    v32 = v32 | r1;

//    pf = (float *)&v32;

//    //!------------------------------
//    //! Обработка отключения устройства
//    if(*pf < float(0.01))
//        *pf = 0;
//    //!------------------------------

////    SEND_TO_LOG( QString("RegToFloat(%1, %2) "
////                         //"{%3, %4, %5, %6} "
////                         "= %3")
////                 .arg(r0).arg(r1)
////                 //.arg(r[0]).arg(r[1]).arg(r[2]).arg(r[3])
////                 .arg(*vf));

//    return *pf;
//}
//------------------------------------------------------------------------------------
//!
QScriptValue RegToFloat(QScriptContext *context, QScriptEngine *engine)
{
    quint16 r0 = context->argument(0).toUInt16();
    quint16 r1 = context->argument(1).toUInt16();

    //SEND_TO_LOG( QString("RegToFloat(%1, %2)").arg(r0).arg(r1) );

    float value = RegToFloatWorker(r0, r1);

    return engine->newVariant( value );
}
//------------------------------------------------------------------------------------
//!
float RegToFloatWorker(const quint16 &r0, const quint16 &r1)
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
        SEND_TO_LOG( QString("RegToFloat(%1, %2) "
                             //"{%3, %4, %5, %6} "
                             "= %3")
                     .arg(r0).arg(r1)
                     //.arg(r[0]).arg(r[1]).arg(r[2]).arg(r[3])
                     .arg(*vf));
    */

    return data.vf;
}
//------------------------------------------------------------------------------------
