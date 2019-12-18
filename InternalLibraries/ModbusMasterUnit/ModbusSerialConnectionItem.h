#ifndef MODBUSSERIALCONNECTIONITEM_H
#define MODBUSSERIALCONNECTIONITEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QObject>

#include "Log.h"
#include "ModbusRegisterItem.h"
#include "ModbusConnectionItem.h"
#include "ModbusMasterConnectionController.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class ModbusSerialConnectionItem : public ModbusConnectionTopicItem
{
    public:
        explicit ModbusSerialConnectionItem(const QString &modbusType,
                                            const QString &topicName,
                                            const QString &uartPortName,
                                            const int baudRate,
                                            const char parity,
                                            const int dataBits,
                                            const int stopBits,
                                            ModbusRegisterItem *parentItem = Q_NULLPTR);

        virtual ~ModbusSerialConnectionItem();


    private:


    private:



};
//------------------------------------------------------------------------------------
#endif // MODBUSSERIALCONNECTIONITEM_H
