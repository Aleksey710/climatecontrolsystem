#include "ModbusRequest.h"

//------------------------------------------------------------------------------------
//!
ModbusRequest::ModbusRequest(const ModbusConnectionSettings &connectionSettings,
                             const quint16 serverAddress,
                             const QModbusPdu::FunctionCode functionCode,
                             const QModbusDataUnit &modbusDataUnit,
                             const int period,
                             QObject *parent)
              :QObject(parent),
               m_connectionSettings ( connectionSettings ),
               m_serverAddress ( serverAddress ),
               m_functionCode ( functionCode ),
               m_modbusDataUnit ( modbusDataUnit )
{
    setObjectName(QString("ModbusRequest[%1]servAddr[%2]f[%3]reg[%4:%5]")
                  .arg(connectionSettings.connectionName)
                  .arg(serverAddress)
                  .arg(m_functionCode)
                  .arg(modbusDataUnit.startAddress())
                  .arg(modbusDataUnit.valueCount())
                  );

#ifndef CIRCULAR_PROCESSING_REQUEST
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        emit wantExecuteQuery(this);
    });
    timer->start(period);
#else

#endif // CIRCULAR_PROCESSING_REQUEST

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
