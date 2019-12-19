#ifndef MODBUSMASTERCONFIGURATOR_H
#define MODBUSMASTERCONFIGURATOR_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
//#include <QtCore/qglobal.h>
#include <QMultiHash>
#include <QHash>
#include <QList>
#include <QDateTime>


#include "Log.h"
#include "ModbusConsts.h"
#include "ModbusSerialConnectionItem.h"
#include "ModbusTcpConnectionItem.h"
#include "ModbusDeviceItem.h"
#include "ModbusRegisterItem.h"
//#include ""
//------------------------------------------------------------------------------------
//!
class ModbusMasterConfigurator
{
    public:
        explicit ModbusMasterConfigurator();

        virtual ~ModbusMasterConfigurator();

    private:
        void sqlResultHandler(QSqlQuery &query);

        void sqlResultSetupDeviceHandler(QSqlQuery &query);

        void sqlResultSetupRegistersHandler(QSqlQuery &query);

        void createModbusRequesters();

    private:
        struct Requester
        {
            Requester()
                :requester_id ( 0 ),
                 period_ms ( 0 ),
                 timeout_ms ( 0 ),
                 function ( 0 ),
                 start_address ( 0 ),
                 isEmpty ( true )
                {  }

            Requester(const int _requester_id,
                      const int _period_ms,
                      const int _timeout_ms,
                      const int _function,
                      const int _start_address)
                :requester_id ( _requester_id ),
                 period_ms ( _period_ms ),
                 timeout_ms ( _timeout_ms ),
                 function ( _function ),
                 start_address ( _start_address ),
                 isEmpty ( false )
                {  }

            int requester_id;
            int period_ms;
            int timeout_ms;
            int function;
            int start_address;

            bool isEmpty;
        };


    private:
        QString m_dpdTopicName;

        QHash<QString, MqttModbusConnectionTopicItem*> m_connectionsItemList;
        QHash<int, ModbusDeviceItem*> m_devicesItemList;

        QMultiHash<int, int> m_device_requesters;

        QHash<int, Requester> m_requestersList;

        //! key - requester_id, value - register_address
        QMultiHash<int, quint16> m_requesterId_register;

};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERCONFIGURATOR_H
