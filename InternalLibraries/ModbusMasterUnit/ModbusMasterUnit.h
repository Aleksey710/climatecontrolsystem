#ifndef MODBUSMASTERUNIT_H
#define MODBUSMASTERUNIT_H
//------------------------------------------------------------------------------------
#include <QObject>
//
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QModbusClient>
#include <QModbusTcpClient>
#include <QModbusRtuSerialMaster>
#include <QModbusPdu>
//
#include <QSerialPort>
//
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
//
#include <QUrl>
#include <QThread>
#include <QMultiHash>
#include <QHash>
#include <QList>
#include <QDateTime>
#include <QQueue>
#include <QSemaphore>
#include <QMutex>
#include <QMutexLocker>

//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusMasterHandler.h"
#include "ModbusMaster485Handler.h"
#include "ModbusRequest.h"
//
#include "ScriptObject.h"
#include "ScriptUnit.h"

//#include ".h"
//#include ".h"
//-------------------------------------------------------------------------
//! В ModbusMasterUnit.pro
//! DEFINES += NATIVE_MODBUS_HANDLER
//! #define NATIVE_MODBUS_HANDLER
//!
//! NATIVE_MODBUS_HANDLER - Использовать модбас обработчик на основе библиотек Qt
//! ИЛИ
//! Использовать модбас обработчик на основе библиотеки
//! https://www.cooking-hacks.com/documentation/tutorials/modbus-module-shield-tutorial-for-arduino-raspberry-pi-intel-galileo/
//-------------------------------------------------------------------------
//! В ModbusMasterUnit.pro
//! DEFINES += CIRCULAR_PROCESSING_REQUEST
//! #define CIRCULAR_PROCESSING_REQUEST
//!
//! Решение1 - циклическое выполнение всех запросов(по очереди)
//! ИЛИ
//! Решение2 - периодическая постановка запросов в очередь на выполнение
//!
//------------------------------------------------------------------------------------
//!
class ModbusMasterUnit : public QObject
{
        Q_OBJECT

    public:
        explicit ModbusMasterUnit(QObject *parent = nullptr);

        virtual ~ModbusMasterUnit();

    signals:
        void setupEnd();

    public slots:

    private slots:
#ifdef CIRCULAR_PROCESSING_REQUEST
        void excuteNextRequest();
#else
        void executeQuery(ModbusRequest *request);
#endif // CIRCULAR_PROCESSING_REQUES

    private:
        QJsonObject loadFile(const QString &fileName);
        void setup(const QJsonObject &jsonObject);

        void connectionParsing(const QJsonObject &connectionJsonObject);
        void deviceParsing(const ModbusConnectionSettings &modbusConnectionSettings,
                           const QJsonObject &deviceJsonObject);

    private:
//-------------------------------------------
#ifdef __arm__
    #ifdef NATIVE_MODBUS_HANDLER
            ModbusMasterHandler     *m_handler;
    #else
            ModbusMaster485Handler  *m_handler;
    #endif // NATIVE_MODBUS_HANDLER
#else // __arm__
     ModbusMasterHandler     *m_handler;
#endif // __arm__
//-------------------------------------------
#ifdef CIRCULAR_PROCESSING_REQUEST
        QTimer *m_pauseTimer;

        //! Решение1 - циклическое выполнение всех запросов(по очереди)
        QList<ModbusRequest*> m_requestList;

        const static int PERIOD_REQUEST_MS          = 1000;
        const static int PERIOD_BETWEEN_REQUEST_MS  = 10;

        uint m_curentRequestId;
#else
        //! Решение2 - периодическая постановка запросов в очередь на выполнение
        QQueue<ModbusRequest*> m_requestQueue;
        QSemaphore m_requestQueueSemaphore;
#endif // CIRCULAR_PROCESSING_REQUEST
//-------------------------------------------

};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNIT_H
