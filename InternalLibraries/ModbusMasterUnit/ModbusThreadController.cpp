#include "ModbusThreadController.h"

//------------------------------------------------------------------------------------
//!
ModbusThreadController::ModbusThreadController(QObject *parent)
                       :QObject(parent)
{
    ModbusMasterHandler *modbusMasterHandler = new ModbusMasterHandler();

    modbusMasterHandler->moveToThread(&m_workerThread);

    connect(&m_workerThread, &QThread::finished, modbusMasterHandler, &QObject::deleteLater);
    connect(this, &ModbusThreadController::operate, modbusMasterHandler, &ModbusMasterHandler::exequteRequest);
    connect(modbusMasterHandler, &ModbusMasterHandler::exequted, this, &ModbusThreadController::exequted);

    //connect(worker, &ModbusMasterHandler::resultReady, this, &ModbusThreadController::handleResults);

    m_workerThread.start();
}
//------------------------------------------------------------------------------------
//!
ModbusThreadController::~ModbusThreadController()
{
    m_workerThread.quit();
    m_workerThread.wait();
}
//------------------------------------------------------------------------------------
//!
