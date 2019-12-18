#ifndef MODBUSTCPCONNECTIONITEM_H
#define MODBUSTCPCONNECTIONITEM_H
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
//------------------------------------------------------------------------------------
//!
class ModbusTcpConnectionItem : public ModbusConnectionTopicItem
{
    public:
        explicit ModbusTcpConnectionItem(const QString &topicName,
                                         const QString &title,
                                         QString ipAddress,
                                         int tcpPort,
                                         ModbusRegisterItem *parentItem = Q_NULLPTR);

        virtual ~ModbusTcpConnectionItem();

    private:


    private:


};
//------------------------------------------------------------------------------------
#endif // MODBUSTCPCONNECTIONITEM_H
