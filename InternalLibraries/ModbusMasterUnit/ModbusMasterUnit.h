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
//#include <>

//#include <>
//#include <>
//#include <>
//#include <>


#include "Log.h"
#include "ModbusConnection.h"
#include "ModbusConnectionSettings.h"
#include "ModbusMasterHandler.h"
#include "ModbusRequest.h"
//
#include "ScriptObject.h"
#include "ScriptUnit.h"

//#include ".h"
//#include ".h"

//-------------------------------------------------------------------------
//! В ModbusMasterUnit.pro
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

    public slots:

    private slots:
#ifdef CIRCULAR_PROCESSING_REQUEST

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
        ModbusMasterHandler *m_handler;

#ifdef CIRCULAR_PROCESSING_REQUEST
        //! Решение1 - циклическое выполнение всех запросов(по очереди)
        QList<ModbusRequest*> m_requestList;

        const static int PERIOD_BETWEEN_REQUEST_MS = 1000;

        QTimer *m_circularTimer;
        int m_curentRequestId;
#else
        //! Решение2 - периодическая постановка запросов в очередь на выполнение
        QQueue<ModbusRequest*> m_requestQueue;
        QSemaphore m_requestQueueSemaphore;
#endif // CIRCULAR_PROCESSING_REQUEST

};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNIT_H
