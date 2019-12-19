#ifndef MODBUSCONNECTIONITEM_H
#define MODBUSCONNECTIONITEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QObject>
#include <QReadWriteLock>
#include <QTimer>

#include "Log.h"
#include "AbstractModbusItem.h"
#include "ModbusMasterConnectionController.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class ModbusConnectionTopicItem : public AbstractModbusItem
{
    public:
        explicit ModbusConnectionTopicItem(const QString &topicName,
                                           AbstractModbusItem *parentItem = Q_NULLPTR);

        virtual ~ModbusConnectionTopicItem();

        ModbusMasterConnectionController* modbusMasterConnectionController()
            { return m_modbusMasterConnectionController; }

    private:


    protected:
        ModbusMasterConnectionController *m_modbusMasterConnectionController;


};
//------------------------------------------------------------------------------------
#endif // MODBUSCONNECTIONITEM_H
