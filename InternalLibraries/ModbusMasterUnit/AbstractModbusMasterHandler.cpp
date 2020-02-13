#include "AbstractModbusMasterHandler.h"

//------------------------------------------------------------------------------------
//!
AbstractModbusMasterHandler::AbstractModbusMasterHandler(QObject *parent)
                            :QObject(parent),
                             m_curentModbusRequest ( nullptr )

{
    setObjectName("ModbusMasterHandler");
    //-------------------------------------------


    //-------------------------------------------
    //SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
AbstractModbusMasterHandler::~AbstractModbusMasterHandler()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
//void AbstractModbusMasterHandler::exequteRequest(ModbusRequest *request)
//{

//}
//------------------------------------------------------------------------------------
//!
void AbstractModbusMasterHandler::errorDataHandler()
{
    if(m_curentModbusRequest)
    {
        QModbusDataUnit modbusDataUnit = m_curentModbusRequest->modbusDataUnit();
        modbusDataUnit.setValues( QVector<quint16>(modbusDataUnit.valueCount(), std::numeric_limits<quint16>::max()) );
        m_curentModbusRequest->setModbusDataUnit(modbusDataUnit, -1);
    }
}
