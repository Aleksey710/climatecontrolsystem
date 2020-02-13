#include "ModbusMaster485Handler.h"
//------------------------------------------------------------------------------------
#ifdef __arm__
    #ifndef NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
//!
ModbusMaster485Handler::ModbusMaster485Handler(QObject *parent)
                       : QObject(parent)
{

}
//------------------------------------------------------------------------------------
//!
ModbusMaster485Handler::~ModbusMaster485Handler()
{

}
//------------------------------------------------------------------------------------
//!
void ModbusMaster485Handler::exequteRequest(ModbusRequest *request)
{
    m_curentModbusRequest = request;

//    SEND_TO_LOG( QString("%1 - -----------------------------").arg(objectName()) );
//    SEND_TO_LOG( QString("%1 - --- start exequte request ---").arg(objectName()) );

    //! Подключение
    if( !reconnect(m_curentModbusRequest->connectionSettings()) )
    {
        exequted();
        return;
    }

    //! Выполнение запроса

    uint8_t result;

    uint16_t address;
    uint16_t quantity;

//    uint16_t readAddress;
//    uint16_t readQuantity;
//    uint16_t writeAddress;
//    uint16_t writeQuantity;

    switch (m_curentModbusRequest->functionCode())
    {
        case 0x01: result = m_mm485->readCoils(address, quantity); break;
        case 0x02: result = m_mm485->readDiscreteInputs(address, quantity); break;
        case 0x03: result = m_mm485->readHoldingRegisters(address, quantity); break;
        case 0x04: result = m_mm485->readInputRegisters(address, quantity); break;
        case 0x05: result = m_mm485->writeSingleCoil(address, quantity); break;
        case 0x06: result = m_mm485->writeSingleRegister(address, quantity); break;
        case 0x0F: result = m_mm485->writeMultipleCoils(address, quantity); break;
        //case value: result = m_mm485->writeMultipleCoils(); break;
        case 0x10: result = m_mm485->writeMultipleRegisters(address, quantity); break;
        //case value: result = m_mm485->writeMultipleRegisters(); break;
        //case 0x16: result = m_mm485->maskWriteRegister(uint16_t, uint16_t, uint16_t); break;
        //case 0x17: result = m_mm485->readWriteMultipleRegisters(readAddress, readQuantity, writeAddress, writeQuantity); break;
        //case 0x17: result = m_mm485->readWriteMultipleRegisters(address, quantity); break;

        default:
            SEND_TO_LOG( QString("%1 - Попытка выполнить необрабатываемую функцию [%2]")
                         .arg(objectName()).arg(m_curentModbusRequest->functionCode()) );
            break;
    }

/*
    switch (m_curentModbusRequest->functionCode())
    {
        case QModbusPdu::ReadCoils:
        case QModbusPdu::ReadDiscreteInputs:
        case QModbusPdu::ReadHoldingRegisters:
        case QModbusPdu::ReadInputRegisters:
            readRequest(m_curentModbusRequest->serverAddress(), m_curentModbusRequest->modbusDataUnit());
            break;
        case QModbusPdu::WriteSingleCoil:
        case QModbusPdu::WriteSingleRegister:
        case QModbusPdu::WriteMultipleCoils:
        case QModbusPdu::WriteMultipleRegisters:
            writeRequest(m_curentModbusRequest->serverAddress(), m_curentModbusRequest->modbusDataUnit());
            break;
        //-------------------------
        case QModbusPdu::Invalid:
        //-------------------------
        case QModbusPdu::ReadExceptionStatus:
        case QModbusPdu::Diagnostics:
        case QModbusPdu::GetCommEventCounter:
        case QModbusPdu::GetCommEventLog:
        case QModbusPdu::ReportServerId:
        case QModbusPdu::ReadFileRecord:
        case QModbusPdu::WriteFileRecord:
        case QModbusPdu::MaskWriteRegister:
        case QModbusPdu::ReadFifoQueue:
        case QModbusPdu::EncapsulatedInterfaceTransport:
        case QModbusPdu::UndefinedFunctionCode:
        default:
            SEND_TO_LOG( QString("%1 - Попытка выполнить необрабатываемую функцию [%2]")
                         .arg(objectName()).arg(m_curentModbusRequest->functionCode()) );
            break;
    }
*/
}
//------------------------------------------------------------------------------------
//!
bool ModbusMaster485Handler::reconnect(const ModbusConnectionSettings &modbusConnectionSettings)
{
    //! Удалить предыдущий обработчик устройства
    deleteModbusDevice();

    setObjectName( QString("ModbusMaster485Handler[%1]").arg(modbusConnectionSettings.connectionName) );

    ModbusConnection modbusConnectionType = modbusConnectionSettings.modbusConnectionType;

    //! Создать обработчик устройства
    if (modbusConnectionType == ModbusConnection::Serial)
    {
        uint8_t slaveAddress = m_curentModbusRequest->serverAddress();

        m_mm485 = new ModbusMaster485(slaveAddress);
    }

    //-------------------------------------
    if (!m_mm485)
    {
        if (modbusConnectionType == ModbusConnection::Serial)
        {
            SEND_TO_LOG( QString("%1 - could not create Modbus master").arg(objectName()) );
        } else
        {
            SEND_TO_LOG( QString("%1 - could not create Modbus client").arg(objectName()) );
        }

        requestExecutionErrorHandler();
        return false;
    } else {

    }

    //--------------------------------------------------
    if (modbusConnectionSettings.modbusConnectionType == ModbusConnection::Serial)
    {
        m_mm485->myDevice.baudRateConfig(modbusConnectionSettings.serialBaudRateParameter);
        m_mm485->myDevice.stopBitConfig(modbusConnectionSettings.serialStopBitsParameter);
        m_mm485->myDevice.parityBit(modbusConnectionSettings.serialParityParameter);

        /*
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                               modbusConnectionSettings.serialPortNameParameter);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                               modbusConnectionSettings.serialParityParameter);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                               modbusConnectionSettings.serialBaudRateParameter);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                               modbusConnectionSettings.serialDataBitsParameter);
        m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                               modbusConnectionSettings.serialStopBitsParameter);
        */
    }

    //--------------------------------------------------
//        if (!m_modbusDevice->connectDevice())
//        {
//            SEND_TO_LOG( QString("%1 - Connect failed: %2")
//                         .arg(objectName())
//                         .arg(m_modbusDevice->errorString()) );

//            requestExecutionErrorHandler();
//            return false;
//        } else
//        {
////            SEND_TO_LOG( QString("%1 - [%2] - is connected")
////                         .arg(objectName())
////                         .arg(modbusConnectionSettings.connectionName) );
//        }

    return true;
}
//------------------------------------------------------------------------------------
//!
void ModbusMaster485Handler::readRequest(const int serverAddress, QModbusDataUnit &readDataUnit)
{

}
//------------------------------------------------------------------------------------
//!
void ModbusMaster485Handler::writeRequest(const int serverAddress, QModbusDataUnit &writeDataUnit)
{

}
//------------------------------------------------------------------------------------
//!
void ModbusMaster485Handler::readWriteRequest(const int serverAddress,
                                              QModbusDataUnit &readDataUnit,
                                              QModbusDataUnit &writeDataUnit)
{

}
//------------------------------------------------------------------------------------
//!
void ModbusMaster485Handler::deleteModbusDevice()
{

}
//------------------------------------------------------------------------------------
//!
void ModbusMaster485Handler::requestExecutionErrorHandler()
{

}

//------------------------------------------------------------------------------------
    #endif // !NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
#endif // __arm__
//------------------------------------------------------------------------------------
