#ifndef MODBUSDEVICEITEM_H
#define MODBUSDEVICEITEM_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QReadWriteLock>
//#include <>
//#include <>

//#include ""
//#include ""
#include "Log.h"
#include "ModbusData.h"
#include "AbstractModbusItem.h"
#include "ModbusRegisterItem.h"
//------------------------------------------------------------------------------------
//!
class ModbusDeviceItem
{
        //! Допустимое количество сбоев в опросе устройства подряд,
        //! которое буедет замаскировано
        static const int ACCEPTABLE_NUMBER_OF_ERROR = 5;

    public:
        explicit ModbusDeviceItem(const QString &topicName,
                                  const quint16 slaveAddress,
                                  const QString &connectionTopicName,
                                  AbstractModbusItem *parentItem = Q_NULLPTR);

        virtual ~ModbusDeviceItem();

        virtual bool setJsonObject(const QJsonObject &jsonObject);

        //! Обработчик данных, приходящих при опросе линии
        void setModbusData(const ModbusData &modbusData);

        inline void addMqttModbusRegisterTopicItem(quint16 regId, ModbusRegisterItem *item)
            { m_regList.insert(regId, item); }

        inline quint16 modbusSlaveAddress()
            { return m_slaveAddress; }

    protected:
        void notificationOfRegisters(const ModbusData &modbusData);

        void alarmDeviceNotification();
        void normalDeviceNotification();

    private:
        QString m_itemName;

        //! Состояние ошибки устройства для отображения
        //    1 - устройство работает
        //    0 - статус устройства неизвестен
        //    -1 - устройство не работает
        //    (все меньше нуля - статусы неработы устройства)

        // Приход libmodbus данных
        // -1 - начальное состояние
        //  0 - норма
        //  остальное - ошибки        
        int m_modbusError;

        //! Счетчик ошибок маскирования
        int m_modbusErrorCount;

        //! true - об аварии уже оповещено (лимит маскирования исчерпан)
        bool m_isAlarmNotifyed;

        QString m_connectionTopicName;
        quint16 m_slaveAddress;

        // Уже есть в DomNodeItem предке
        //DataStorage             m_dataStorage;

        QHash<quint16, ModbusRegisterItem*> m_regList;

        //----------------------------------------------
        int m_normalNotificationCount;
};
//------------------------------------------------------------------------------------
#endif // MODBUSDEVICEITEM_H
