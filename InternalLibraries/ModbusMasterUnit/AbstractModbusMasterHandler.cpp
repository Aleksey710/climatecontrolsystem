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
