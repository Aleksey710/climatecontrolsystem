#include "ModbusRequest.h"

//------------------------------------------------------------------------------------
//!
ModbusRequest::ModbusRequest(const ModbusConnectionSettings &connectionSettings,
                             const quint16 deviceAddress,
                             //QModbusDataUnit unit,
                             const int period,
                             QObject *parent)
              :QObject(parent),
               m_connectionSettings ( connectionSettings ),
               m_deviceAddress ( deviceAddress )
{
    setObjectName(QString("ModbusRequest[%1][%2]")
                  .arg(connectionSettings.connectionName)
                  .arg(deviceAddress)
                  );

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        emit wantExecuteQuery(this);
    });
    timer->start(period);
}
//------------------------------------------------------------------------------------
//!
ModbusRequest::~ModbusRequest()
{

}
//------------------------------------------------------------------------------------
//!
void ModbusRequest::processRequest()
{

}
