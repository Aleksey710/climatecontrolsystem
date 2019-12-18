#ifndef MODBUSMASTERCONNECTION_H
#define MODBUSMASTERCONNECTION_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <functional>
#include <QList>
#include <QQueue>
#include <QMutex>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "ModbusRequest.h"
#include "ModbusData.h"
#include "ModbusConnectionAddress.h"

#include "Log.h"
#include "ModbusMaster.h"
#include "ModbusSlave.h"
#include "ModbusPartner.h"
#include "ModbusRequester.h"
//------------------------------------------------------------------------------------
//!
class ModbusMasterConnection : public QObject
{
        Q_OBJECT

    private:
        //! http://www.modbus.org/docs/Modbus_over_serial_line_V1_02.pdf
        //! По стандарту между кадрами(frame) должен быть временной интервал больше 3,5 символа
        //! Для быстрых скоростей(115200) и с учетом специфики работы таймеров НЕ в режиме реального времени
        //! рекомендовано соблюдать временной интервал не менее 1,7 ms.
        //! __useconds_t - Count of microseconds.
        __useconds_t PAUSE_BETWEEN_REQUESTS_MS = 10;

    public:
        explicit ModbusMasterConnection(const QString &coreType,
                                        const ModbusConnectionAddress &modbusConnectionAddress,
                                        QObject *parent = nullptr);

        virtual ~ModbusMasterConnection();



    signals:
        void newData(const ModbusData &data, int slaveAddress);

    public slots:
        void init();

        void addRequester(const ModbusRequest &modbusRequest,
                          int period);

    private slots:


    private:
        void executeTask();


    private:
        QMutex                  m_mutex;
        QString                 m_coreType;
        ModbusConnectionAddress m_modbusConnectionAddress;

        ModbusMaster            *m_modbusMaster;

        QList<ModbusRequester*> m_modbusRequesterList;

        //QQueue< std::function<void()>* >  m_requestQueue;
        QQueue< ModbusRequest* >  m_requestQueue;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERCONNECTION_H
