#include "ModbusDeviceItem.h"

//------------------------------------------------------------------------------------
//!
ModbusDeviceItem::ModbusDeviceItem(const QString &topicName,
                                   const quint16 slaveAddress,
                                   const QString &connectionTopicName,
                                   AbstractModbusItem *parentItem)
                 :AbstractModbusItem(topicName, parentItem),
                  m_modbusError ( -1 ),
                  m_modbusErrorCount ( 0 ),
                  m_isAlarmNotifyed ( false ),
                  m_connectionTopicName ( connectionTopicName ),
                  m_slaveAddress ( slaveAddress ),
                  m_normalNotificationCount ( 0 )
{    
    m_itemName = QString("ModbusDeviceItem[%1 addr: 0x%2]")
                .arg(m_connectionTopicName)
                .arg(m_slaveAddress, 0, 16);

    //! Для соблюдения целостности
    initForcedNotificationTimer();
}
//------------------------------------------------------------------------------------
//!
ModbusDeviceItem::~ModbusDeviceItem()
{

}
//------------------------------------------------------------------------------------
//!
bool ModbusDeviceItem::setJsonObject(const QJsonObject &jsonObject)
{
    if(m_publisher)
    {
        m_publisher->jsonObjectPublish(jsonObject, MqttTopicMsgType::JsonData);
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------
//! Обработчик данных, приходящих при опросе линии
void ModbusDeviceItem::setModbusData(const ModbusData &modbusData)
{
    //qDebug() << "ModbusDeviceItem::setModbusData" << itemName() << modbusData.info();
    //! для индикации
    //    1 - устройство работает
    //    0 - статус устройства неизвестен
    //    -1 - устройство не работает
    //    (все меньше нуля - статусы неработы устройства)

    // Приходит
    // 0 - libmodbus норма
    // остальное - ошибки
    //---------------------------------
    //! Если нет libmodbus ошибок
    if(modbusData.stateError == 0)
    {
        //! Если востановление работы
        //! Прошлый приход данных от libmodbus был с атрибутом ошибки
        if(m_modbusError != 0)
        {
            //! Сбросить счетчик ошибок маскирования
            m_modbusErrorCount = 0;

            //! Об аварии еще не сообщено (сброс флага)
            m_isAlarmNotifyed = false;

            //--------------------------------------------
            //! Сохранить новое значение состояния ошибок
            //! 0 - нет ошибок
            m_modbusError = 0;

            SEND_TO_LOG( QString("%1 - востановлена работоспособность устройства")
                         .arg(m_itemName)
                       );

            //----------------------------------------------------------------
            //! Оповещение о состоянии устройства
            normalDeviceNotification();

            return;
        }

        //----------------------------------------------------------------
        //! Костыль если(пока) не налажено нормально оповещение о состоянии устройств
        //! при нормальной работе - оповещать каждым 5 сообщением
        m_normalNotificationCount++;

        if(m_normalNotificationCount > 5)
        {
            //! Оповестить, что устройство в норме
            normalDeviceNotification();

            m_normalNotificationCount = 0;
        }

        //----------------------------------------------------------------
        //! Оповещение регистров
        notificationOfRegisters(modbusData);
    } else
    //! Есть ошибки
    {
        //! признак необходимости оповещения
        bool isNotify = false;

        //! Увеличить значение счетчика ошибок
        m_modbusErrorCount++;

        //! Если раньше была норма
        //! (rc=0) - норма в libmodbus
        if(m_modbusError == 0)
        {
            //! Сохранить новое значение состояния ошибок
            m_modbusError = modbusData.stateError;

            SEND_TO_LOG( QString("%1 - ошибка опроса устройства [№%2] - cod %3 %4")
                         .arg(m_itemName)
                         .arg(m_modbusErrorCount)
                         .arg(m_modbusError)
                         .arg(modbusData.stateErrorString())
                       );

        } else
        //! Если раньше была ошибка
        {
            //! Если раньше была ДРУГАЯ ошибка
            if(m_modbusError != modbusData.stateError)
            {
                //! Сохранить новое значение состояния ошибок
                m_modbusError = modbusData.stateError;

                //! Если еще не было оповещено
                if( !m_isAlarmNotifyed )
                {
                    SEND_TO_LOG( QString("%1 - поменялось состояние ошибки устройства [№%2] - cod %3 %4")
                                 .arg(m_itemName)
                                 .arg(m_modbusErrorCount)
                                 .arg(modbusData.stateError)
                                 .arg(modbusData.stateErrorString())
                               );
                }
                //! Флаг сигнализирования
                //isNotify = true;
            } else
            {
                //! Если еще не было оповещено
                if( !m_isAlarmNotifyed )
                {
                    SEND_TO_LOG( QString("%1 - ошибка опроса устройства [№%2] - cod %3 %4")
                                 .arg(m_itemName)
                                 .arg(m_modbusErrorCount)
                                 .arg(modbusData.stateError)
                                 .arg(modbusData.stateErrorString())
                               );
                }
            }

            //---------------------------------------------------------------------------
            //! Если количество сообщений с ошибкой превысило допустимый предел
            if(m_modbusErrorCount >= ACCEPTABLE_NUMBER_OF_ERROR)
            {
                //! Если еще не было оповещено
                if( !m_isAlarmNotifyed )
                {
                    //! Установить флаг оповещения
                    m_isAlarmNotifyed = true;

                    SEND_TO_LOG( QString("%1 - ошибка опроса устройства [№%2] - превышен предел маскирования")
                                 .arg(m_itemName)
                                 .arg(m_modbusErrorCount)
                                );

                    //! Сигнализировать
                    isNotify = true;
                }

                //! Держать в превышении, но недавать рости
                m_modbusErrorCount = ACCEPTABLE_NUMBER_OF_ERROR + 1;
            }
        }

        //---------------------------------------------------------------------------
        //! Обработка изменения состояния
        if(isNotify)
        {
            //! Состояние устройства уже своими данными сигнализирует об ошибке
            //! По этому на него общесистемная сигнализация не распространяется
            alarmDeviceNotification();

            //----------------------------------------------------------------------------------------------
//            qDebug() << "MqttModbusDeviceTopicItem::setModbusData"
//                     << itemName() << m_modbusErrorCount << m_acceptableNumberOfError << m_isAlarmNotifyed;

            notificationOfRegisters(modbusData);
        }
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusDeviceItem::alarmDeviceNotification()
{
    QJsonObject jsonObject;
    //! The device is DAMAGED!!!
    jsonObject.insert(QStringLiteral("0"), QStringLiteral("-1"));
    //! Передать новое состояние
    setJsonObject(jsonObject);

    m_forcedNotificationTimer->restartWork();
}
//------------------------------------------------------------------------------------
//!
void ModbusDeviceItem::normalDeviceNotification()
{
    QJsonObject jsonObject;
    //! The device has been fixed
    jsonObject.insert(QStringLiteral("0"), QStringLiteral("1"));
    //! Передать новое состояние
    setJsonObject(jsonObject);

    m_forcedNotificationTimer->restartWork();
}
//------------------------------------------------------------------------------------
//!
void ModbusDeviceItem::notificationOfRegisters(const ModbusData &modbusData)
{
    //qDebug() << "MqttModbusDeviceTopicItem::notificationOfRegisters";

    //! Получить состояние ошибки запроса
    //! (0 - нет ошибок)
    int stateError = modbusData.stateError;

    //-----------------------------------------------------------------------------------
    QHash<quint16, ModbusRegisterItem*>::const_iterator i = m_regList.constBegin();

    //! Перебрать регистры
    for (i = m_regList.constBegin(); i != m_regList.constEnd(); ++i)
    {
        quint16 number = i.key();

        //! Получить данные по регистру
        quint16 modbusRegisterData = modbusData.getData(number);

        //-------------------------------------------------------------
        ModbusRegisterItem *registerTopicItem = i.value();

        //! Передать данные по регистру(данные , состояние ошибки) в обработчик топика регистра
        registerTopicItem->setModbusRegisterData(modbusRegisterData, stateError, modbusData.stateErrorString());
    }

}
