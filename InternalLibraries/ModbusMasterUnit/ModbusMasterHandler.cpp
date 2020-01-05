#include "ModbusMasterHandler.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterHandler::ModbusMasterHandler(QObject *parent)
                    :QObject(parent),
                     m_modbusDevice ( nullptr ),
                     m_curentModbusRequest ( nullptr )
{
    setObjectName("ModbusMasterHandler");
    //-------------------------------------------


    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterHandler::~ModbusMasterHandler()
{
    if (m_modbusDevice)
        m_modbusDevice->disconnectDevice();
    delete m_modbusDevice;
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::exequteRequest(ModbusRequest *request)
{
    m_curentModbusRequest = request;
    SEND_TO_LOG( QString("%1 - -----------------------------").arg(objectName()) );
    SEND_TO_LOG( QString("%1 - --- start exequte request ---").arg(objectName()) );
    //! Подключение
    reconnect(request->connectionSettings());

    //! Выполнение запроса
    switch (request->functionCode())
    {
        case QModbusPdu::ReadCoils:
        case QModbusPdu::ReadDiscreteInputs:
        case QModbusPdu::ReadHoldingRegisters:
        case QModbusPdu::ReadInputRegisters:
            readRequest(request->serverAddress(), request->modbusDataUnit());
            break;
        case QModbusPdu::WriteSingleCoil:
        case QModbusPdu::WriteSingleRegister:
            writeRequest(request->serverAddress(), request->modbusDataUnit());
            break;
        //-------------------------
        case QModbusPdu::Invalid:
        //-------------------------
        case QModbusPdu::ReadExceptionStatus:
        case QModbusPdu::Diagnostics:
        case QModbusPdu::GetCommEventCounter:
        case QModbusPdu::GetCommEventLog:
        case QModbusPdu::WriteMultipleCoils:
        case QModbusPdu::WriteMultipleRegisters:
        case QModbusPdu::ReportServerId:
        case QModbusPdu::ReadFileRecord:
        case QModbusPdu::WriteFileRecord:
        case QModbusPdu::MaskWriteRegister:
        case QModbusPdu::ReadFifoQueue:
        case QModbusPdu::EncapsulatedInterfaceTransport:
        case QModbusPdu::UndefinedFunctionCode:
        default:
            SEND_TO_LOG( QString("%1 - Попытка выполнить необрабатываемую функцию [%2]")
                         .arg(objectName()).arg(request->functionCode()) );
            break;
    }
    //m_handler->readWriteRequest(request->serverAddress(), readDataUnit, writeDataUnit);
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::reconnect(const ModbusConnectionSettings &modbusConnectionSettings)
{
    //! Удалить предыдущий обработчик устройства
    if (m_modbusDevice)
    {
        m_modbusDevice->disconnectDevice();
        delete m_modbusDevice;
        m_modbusDevice = nullptr;
    }

    setObjectName( QString("ModbusMasterHandler[%1]").arg(modbusConnectionSettings.connectionName) );

    ModbusConnection modbusConnectionType = modbusConnectionSettings.modbusConnectionType;

    //! Создать обработчик устройства
    if (modbusConnectionType == Serial)
    {
        m_modbusDevice = new QModbusRtuSerialMaster(this);
    } else if (modbusConnectionType == Tcp)
    {
        m_modbusDevice = new QModbusTcpClient(this);
    }

    if (!m_modbusDevice)
        return;

    connect(m_modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error) {
        SEND_TO_LOG( QString("%1 - %2")
                     .arg(objectName())
                     .arg(m_modbusDevice->errorString()) );
    });

    if (!m_modbusDevice)
    {
        if (modbusConnectionType == Serial)
        {
            SEND_TO_LOG( QString("%1 - could not create Modbus master").arg(objectName()) );
        } else
        {
            SEND_TO_LOG( QString("%1 - could not create Modbus client").arg(objectName()) );
        }
    } else {
        connect(m_modbusDevice, &QModbusClient::stateChanged,
                [this](QModbusDevice::State state) {

            switch (state)
            {
                case QModbusDevice::UnconnectedState:
                    SEND_TO_LOG( QString("%1 - UnconnectedState").arg(objectName()) );
                    break;
                case QModbusDevice::ConnectingState:
                    //SEND_TO_LOG( QString("%1 - ConnectingState").arg(objectName()) );
                    break;
                case QModbusDevice::ConnectedState:
                    //SEND_TO_LOG( QString("%1 - ConnectedState").arg(objectName()) );
                    break;
                case QModbusDevice::ClosingState:
                    //SEND_TO_LOG( QString("%1 - ClosingState").arg(objectName()) );
                    break;
                default:
                    break;
            }
        });
    }

    //--------------------------------------------------
    if (m_modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        if (modbusConnectionSettings.modbusConnectionType == Serial)
        {
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
        } else {
            m_modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter,
                modbusConnectionSettings.networkPortParameter);
            m_modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter,
                modbusConnectionSettings.networkAddressParameter);
        }

        m_modbusDevice->setTimeout(modbusConnectionSettings.responseTime);
        m_modbusDevice->setNumberOfRetries(modbusConnectionSettings.numberOfRetries);

        if (!m_modbusDevice->connectDevice())
        {
            SEND_TO_LOG( QString("%1 - Connect failed: %2")
                         .arg(objectName())
                         .arg(m_modbusDevice->errorString()) );
        } else
        {
            SEND_TO_LOG( QString("%1 - [%2] - is connected")
                         .arg(objectName())
                         .arg(modbusConnectionSettings.connectionName) );
        }
    } else {
        m_modbusDevice->disconnectDevice();
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::readRequest(const int serverAddress, QModbusDataUnit &readDataUnit)
{
    SEND_TO_LOG( QString("%1 - read request addr[%2]").arg(objectName()).arg(serverAddress) );

    if (!m_modbusDevice)
        return;

    if (auto *reply = m_modbusDevice->sendReadRequest(readDataUnit, serverAddress))
    {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &ModbusMasterHandler::readReady);
        else
            // broadcast replies return immediately
            delete reply;
    } else {
        SEND_TO_LOG( QString("%1 - Read error: %2")
                     .arg(objectName())
                     .arg(m_modbusDevice->errorString()) );
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::writeRequest(const int serverAddress, QModbusDataUnit &writeDataUnit)
{
    if (!m_modbusDevice)
        return;

    //QModbusDataUnit writeUnit = writeRequest();
/*
    QModbusDataUnit::RegisterType table = dataUnit.registerType();

    for (uint i = 0; i < dataUnit.valueCount(); i++)
    {
        if (table == QModbusDataUnit::Coils)
            dataUnit.setValue(i, writeModel->m_coils[i + writeUnit.startAddress()]);
        else
            dataUnit.setValue(i, writeModel->m_holdingRegisters[i + writeUnit.startAddress()]);
    }
*/
    if ( auto *reply = m_modbusDevice->sendWriteRequest(writeDataUnit, serverAddress) )
    {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this, [this, reply]()
            {
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    SEND_TO_LOG( QString("%1 - Write response error: %2 (Mobus exception: 0x%3)")
                                 .arg(objectName())
                                 .arg(reply->errorString())
                                 .arg(reply->rawResult().exceptionCode(), -1, 16)
                               );

                } else if (reply->error() != QModbusDevice::NoError)
                {
                    SEND_TO_LOG( QString("%1 - Write response error: %2 (code: 0x%3)")
                                 .arg(objectName())
                                 .arg(reply->errorString())
                                 .arg(reply->error(), -1, 16)
                               );
                }

                reply->deleteLater();
            });
        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        SEND_TO_LOG( QString("%1 - Write response error: %2")
                     .arg(objectName())
                     .arg(m_modbusDevice->errorString())
                   );
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::readWriteRequest(const int serverAddress,
                                        QModbusDataUnit &readDataUnit,
                                        QModbusDataUnit &writeDataUnit)
{
    if (!m_modbusDevice)
        return;

//    ui->readValue->clear();
//    statusBar()->clearMessage();

//    QModbusDataUnit writeUnit = writeRequest();
    /*
    QModbusDataUnit::RegisterType table = writeUnit->registerType();

    for (uint i = 0; i < writeUnit->valueCount(); i++)
    {
        if (table == QModbusDataUnit::Coils)
            writeUnit->setValue(i, writeModel->m_coils[i + writeUnit.startAddress()]);
        else
            writeUnit->setValue(i, writeModel->m_holdingRegisters[i + writeUnit.startAddress()]);
    }
    */

    if ( auto *reply = m_modbusDevice->sendReadWriteRequest(readDataUnit, writeDataUnit, serverAddress) )
    {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &ModbusMasterHandler::readReady);
        else
            delete reply; // broadcast replies return immediately
    } else {
        SEND_TO_LOG( QString("%1 - Read error: %2")
                     .arg(objectName())
                     .arg(m_modbusDevice->errorString())
                   );
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    replyHandler(reply);
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::replyHandler(QModbusReply *reply)
{
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();

        //-----------------------------------
        m_curentModbusRequest->setModbusDataUnit(unit);
        //-----------------------------------
        for (uint i = 0; i < unit.valueCount(); i++)
        {
            const QString entry = tr("Address: %1, Value: %2")
                                  .arg(unit.startAddress() + i)
                                  .arg(QString::number(unit.value(i),
                                                       unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16)
                                       );
            SEND_TO_LOG( QString("%1 - data: %2").arg(objectName()).arg(entry) );
        }
    } else if (reply->error() == QModbusDevice::ProtocolError)
    {
        SEND_TO_LOG( QString("%1 - Read response error: %2 (Mobus exception: 0x%3 [%4])")
                     .arg(objectName())
                     .arg(reply->errorString())
                     .arg(reply->rawResult().exceptionCode(), -1, 16)
                     .arg(modbusExceptionCodeToString(reply->rawResult().exceptionCode()))
                   );
    } else {
        SEND_TO_LOG( QString("%1 - Read response error: %2 (code: 0x%3)")
                     .arg(objectName())
                     .arg(reply->errorString())
                     .arg(reply->error(), -1, 16)
                   );
    }

    reply->deleteLater();

    //-----------------------------------
    SEND_TO_LOG( QString("%1 - --- end exequte request -----").arg(objectName()) );
    SEND_TO_LOG( QString("%1 - -----------------------------").arg(objectName()) );

    emit exequted();
}
//------------------------------------------------------------------------------------
//!
QString ModbusMasterHandler::modbusExceptionCodeToString(const QModbusPdu::ExceptionCode &code)
{
    switch (code)
    {
        case QModbusPdu::IllegalFunction:
            return "Illegal function";
            break;
        case QModbusPdu::IllegalDataAddress:
            return "Illegal data address";
            break;
        case QModbusPdu::IllegalDataValue:
            return "Illegal data value";
            break;
        case QModbusPdu::ServerDeviceFailure:
            return "Server device failure";
            break;
        case QModbusPdu::Acknowledge:
            return "Acknowledge";
            break;
        case QModbusPdu::ServerDeviceBusy:
            return "Server device busy";
            break;
        case QModbusPdu::NegativeAcknowledge:
            return "Negative acknowledge";
            break;
        case QModbusPdu::MemoryParityError:
            return "Memory parity error";
            break;
        case QModbusPdu::GatewayPathUnavailable:
            return "Gateway path unavailable";
            break;
        case QModbusPdu::GatewayTargetDeviceFailedToRespond:
            return "Gateway target device failed to respond";
            break;
        case QModbusPdu::ExtendedException:
            return "Extended exception";
            break;
        default:
            break;
    }
    return QString();
}
//------------------------------------------------------------------------------------
//!
/*
QString ModbusMasterHandler::modbusDeviceErrorToString(const QModbusDevice::Error &error)
{
    switch (error)
    {
        case QModbusDevice::NoError:
            return "No error";
            break;
        case QModbusDevice::ReadError:
            return "Read error";
            break;
        case QModbusDevice::WriteError:
            return "Write error";
            break;
        case QModbusDevice::ConnectionError:
            return "Connection error";
            break;
        case QModbusDevice::ConfigurationError:
            return "Configuration error";
            break;
        case QModbusDevice::TimeoutError:
            return "Timeout error";
            break;
        case QModbusDevice::ProtocolError:
            return "Protocol error";
            break;
        case QModbusDevice::ReplyAbortedError:
            return "ReplyAborted error";
            break;
        case QModbusDevice::UnknownError:
            return "Unknown error";
            break;
        default:
            break;
    }
}
*/
/*
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::on_writeTable_currentIndexChanged(int index)
{
    const bool coilsOrHolding = index == 0 || index == 3;
    if (coilsOrHolding) {
        ui->writeValueTable->setColumnHidden(1, index != 0);
        ui->writeValueTable->setColumnHidden(2, index != 3);
        ui->writeValueTable->resizeColumnToContents(0);
    }

    ui->readWriteButton->setEnabled(index == 3);
    ui->writeButton->setEnabled(coilsOrHolding);
    ui->writeGroupBox->setEnabled(coilsOrHolding);
}

//------------------------------------------------------------------------------------
//!
QModbusDataUnit ModbusMasterUnit::readRequest() const
{
    const auto table =
        static_cast<QModbusDataUnit::RegisterType> (ui->writeTable->currentData().toInt());

    int startAddress = ui->readAddress->value();
    Q_ASSERT(startAddress >= 0 && startAddress < 10);

    // do not go beyond 10 entries
    int numberOfEntries = qMin(ui->readSize->currentText().toInt(), 10 - startAddress);
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}
//------------------------------------------------------------------------------------
//!
QModbusDataUnit ModbusMasterUnit::writeRequest() const
{
    const auto table =
        static_cast<QModbusDataUnit::RegisterType> (ui->writeTable->currentData().toInt());

    int startAddress = ui->writeAddress->value();
    Q_ASSERT(startAddress >= 0 && startAddress < 10);

    // do not go beyond 10 entries
    int numberOfEntries = qMin(ui->writeSize->currentText().toInt(), 10 - startAddress);
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}
*/
