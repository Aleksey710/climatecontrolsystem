#ifndef MODBUSMASTERUNIT_H
#define MODBUSMASTERUNIT_H
//------------------------------------------------------------------------------------
#include <QObject>
//
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
//
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
#include "ModbusConnectionSettings.h"
#include "ModbusMasterHandler.h"
#include "ModbusThreadController.h"
#include "ModbusRequest.h"
//
#include "ScriptObject.h"
#include "ScriptUnit.h"

//#include ".h"
//#include ".h"
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
        ModbusThreadController  *m_modbusThreadController;
        //ModbusMasterHandler     *m_handler;

//-------------------------------------------
#ifdef CIRCULAR_PROCESSING_REQUEST
        QTimer *m_pauseTimer;

        //! Решение1 - циклическое выполнение всех запросов(по очереди)
        QList<ModbusRequest*> m_requestList;

        const static int PERIOD_REQUEST_MS          = 1000;
        const static int PERIOD_BETWEEN_REQUEST_MS  = 200;

        int m_curentRequestId;
#else
        //! Решение2 - периодическая постановка запросов в очередь на выполнение
        QQueue<ModbusRequest*> m_requestQueue;
        QSemaphore m_requestQueueSemaphore;
#endif // CIRCULAR_PROCESSING_REQUEST
//-------------------------------------------

};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNIT_H
