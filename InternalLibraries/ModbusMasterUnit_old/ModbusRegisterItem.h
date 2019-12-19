#ifndef MODBUSREGISTERITEM_H
#define MODBUSREGISTERITEM_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QReadWriteLock>
//#include <>
//#include <>

//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "modbus.h"
#include "AbstractModbusItem.h"
//------------------------------------------------------------------------------------
//!
class ModbusRegisterItem : public AbstractModbusItem
{
    public:
        explicit ModbusRegisterItem(const QString &topicName,
                                             const quint16 registerNumber,
                                             const QString &errorStringTitle,
                                             AbstractModbusItem *parentItem = Q_NULLPTR);

        virtual ~ModbusRegisterItem();

        inline quint16 number()
            { return m_registerNumber; }

        virtual bool setJsonObject(const QJsonObject &jsonObject);

        void setModbusRegisterData(quint16 modbusRegisterData,
                                   int modbusError,
                                   const QString &stateErrorString = QStringLiteral(""));

    protected:
        //! Оповещение об ошибке
        void errorNotified(int modbusError,
                           const QString &stateErrorString = QStringLiteral(""));


    private:
        quint16 m_registerNumber;

        quint16 m_modbusRegisterData;

        // Приход данных
        // -1 - начальное состояние
        //  0 - норма
        //  остальное - ошибки
        int m_modbusError;

        const QString     m_errorStringTitle;
        QString           m_stateErrorString;

        // Уже есть в DomNodeItem предке
        //DataStorage             m_dataStorage;
};
//------------------------------------------------------------------------------------
#endif // MODBUSREGISTERITEM_H
