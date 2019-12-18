#ifndef MODBUSTYPE_H
#define MODBUSTYPE_H
//------------------------------------------------------------------------------------
#include <QString>

//------------------------------------------------------------------------------------
// #include "ModbusType.h"
//------------------------------------------------------------------------------------
//!
typedef enum {
    NONE    = 0,
    RTU     = 1,
    TCP     = 2,
    ASCII   = 3,
    ISI     = 4
} ModbusType;
//------------------------------------------------------------------------------------
//!
inline QString modbusTypeToString(ModbusType &type)
{
    switch (type)
    {
        case NONE:
            return QStringLiteral("NONE");
            break;
        case RTU:
            return QStringLiteral("RTU");
            break;
        case TCP:
            return QStringLiteral("TCP");
            break;
        case ASCII:
            return QStringLiteral("ASCII");
            break;
        case ISI:
            return QStringLiteral("ISI");
            break;
        default:
            break;
    }

    return QStringLiteral("");
}
//------------------------------------------------------------------------------------
//!
inline ModbusType modbusStringToType(const QString &str)
{
    ModbusType type = NONE;

    if(str == QStringLiteral("RTU"))
    {
        type = RTU;
    } else if(str == QStringLiteral("TCP"))
    {
        type = TCP;
    } else if(str == QStringLiteral("ASCII"))
    {
        type = ASCII;
    } else if(str == QStringLiteral("ISI"))
    {
        type = ISI;
    }

    return type;
}
//------------------------------------------------------------------------------------
#endif // MODBUSTYPE_H
