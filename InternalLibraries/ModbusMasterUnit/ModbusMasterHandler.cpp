#include "ModbusMasterHandler.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterHandler::ModbusMasterHandler(QObject *parent)
//                    :NativeModbusMasterHandler(parent)
                    :LibmodbusModbusMasterHandler(parent)
//                    :ModbusMaster485Handler(parent)
{
    setObjectName("ModbusMasterHandler");
    //-------------------------------------------


    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterHandler::~ModbusMasterHandler()
{    
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
