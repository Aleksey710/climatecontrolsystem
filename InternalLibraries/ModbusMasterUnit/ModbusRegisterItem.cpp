#include "ModbusRegisterItem.h"

//------------------------------------------------------------------------------------
//!
ModbusRegisterItem::ModbusRegisterItem(const QString &topicName,
                                                         const quint16 registerNumber,
                                                         const QString &errorStringTitle,
                                                         AbstractModbusItem *parentItem)
                            :AbstractModbusItem(topicName, parentItem),
                             m_registerNumber ( registerNumber ),
                             m_modbusRegisterData ( 0 ),
                             m_modbusError (-1),
                             m_errorStringTitle ( errorStringTitle )
{
    //! Для соблюдения целостности
    initForcedNotificationTimer();

    //qDebug() << fullTopicName() << m_errorStringTitle;
}
//------------------------------------------------------------------------------------
//!
ModbusRegisterItem::~ModbusRegisterItem()
{

}
//------------------------------------------------------------------------------------
//!
bool ModbusRegisterItem::setJsonObject(const QJsonObject &jsonObject)
{
    if(m_publisher)
    {
        m_publisher->jsonObjectPublish(jsonObject, MqttTopicMsgType::JsonData);
        return true;
    }

    return false;
}
//------------------------------------------------------------------------------------
//!
void ModbusRegisterItem::setModbusRegisterData(quint16 modbusRegisterData,
                                                        int modbusError,
                                                        const QString &stateErrorString)
{
    //qDebug() << "MqttModbusRegisterTopicItem2::setModbusRegisterData" << modbusRegisterData << modbusError;

    //! Если по Modbus ошибок нет
    //! (новые данные без ошибок)
    if(modbusError == 0)
    {
        //! флаг оповещения
        bool isNotified = false;

        //! Исправление с ERROR на NORMAL
        if(m_modbusError != modbusError)
        {
            //! Сохранить новое значение состояния ошибок (0 - ошибок нет)
            m_modbusError = 0;
            isNotified = true;
        }

        //! Проверка на изменение данных
        //! Ускоренное сравнение (quint16 вместо QVariant)
        if(m_modbusRegisterData != modbusRegisterData)
        {
            //! Сохранить новые данные
            m_modbusRegisterData = modbusRegisterData;
            isNotified = true;
        }

        if(isNotified)
        {
            const QJsonObject jsonObject{
                { QStringLiteral("0"), QString::number(m_modbusRegisterData) }
            };
            setJsonObject(jsonObject);

            //qDebug() << "MqttModbusRegisterTopicItem2::setModbusRegisterData" << modbusRegisterData << modbusError;
        } else
        {
            //! будет срабатывать initForcedNotificationTimer();
            //! и оповещать для соблюдения целостности
        }
    } else
    //! Данные с ошибкой
    {
        //! Сохранить код ошибки
        m_modbusError = modbusError;

        //! Оповестить об ошибке
        errorNotified(modbusError, stateErrorString);
    }
}
//------------------------------------------------------------------------------------
//! Оповещение об ошибке
void ModbusRegisterItem::errorNotified(int modbusError,
                                                const QString &stateErrorString)
{
    const QJsonObject jsonObject {
        { QStringLiteral("0"),      QStringLiteral("0") },
        { QStringLiteral("200"),    QJsonArray {
                                        QString("%1 - cod[%2] (%3)")
                                            .arg(m_errorStringTitle)
                                            .arg(modbusError)
                                            .arg(stateErrorString),
                                    }
        }
    };

//    //! 0 в значение данных
//    jsonObject.insert(QStringLiteral("0"), QStringLiteral("0"));

//    QJsonArray errorJsonArray;

//    //! Сформировать строку описание ошибки
//    QString errorStr = ;

//    errorJsonArray.append(errorStr);
//    jsonObject.insert(QStringLiteral("200"), errorJsonArray);

    setJsonObject(jsonObject);
}
