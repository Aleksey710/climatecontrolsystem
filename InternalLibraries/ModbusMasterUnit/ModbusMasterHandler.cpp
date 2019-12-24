#include "ModbusMasterHandler.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterHandler::ModbusMasterHandler(QObject *parent)
                    :QObject(parent),
                      m_modbusDevice( nullptr )
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
void ModbusMasterHandler::updateObjectName()
{
    QString name;

    //! Создать обработчик устройства
    if (m_modbusConnectionSettings->modbusConnectionType == Serial)
    {
        QString parityString;

        switch (m_modbusConnectionSettings->serialParityParameter)
        {
            case QSerialPort::NoParity:
                parityString = "N";
                break;
            case QSerialPort::EvenParity:
                parityString = "E";
                break;
            case QSerialPort::OddParity:
                parityString = "O";
                break;
            case QSerialPort::SpaceParity:
                parityString = "S";
                break;
            case QSerialPort::MarkParity:
                parityString = "M";
                break;
            case QSerialPort::UnknownParity:
            default:
                parityString = "U";
                break;
        }

        name = QString("RTU[%1(%2)%3%4%5]")
               .arg(m_modbusConnectionSettings->serialPortNameParameter)
               .arg(m_modbusConnectionSettings->serialBaudRateParameter)
               .arg(m_modbusConnectionSettings->serialDataBitsParameter)
               .arg(parityString)
               .arg(m_modbusConnectionSettings->serialStopBitsParameter)
                ;
    } else if (m_modbusConnectionSettings->modbusConnectionType == Tcp)
    {
        name = QString("TCP[%1:%2]")
               .arg(m_modbusConnectionSettings->networkAddressParameter)
               .arg(m_modbusConnectionSettings->networkPortParameter);
    }

    setObjectName( QString("ModbusMasterUnit[%1]").arg(name) );
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::reconnect(const ModbusConnectionSettings &modbusConnectionSettings)
{
    m_modbusConnectionSettings = std::make_shared<ModbusConnectionSettings>( modbusConnectionSettings );

    //! Удалить предыдущий обработчик устройства
    if (m_modbusDevice)
    {
        m_modbusDevice->disconnectDevice();
        delete m_modbusDevice;
        m_modbusDevice = nullptr;
    }

    updateObjectName();

    ModbusConnection modbusConnectionType = m_modbusConnectionSettings->modbusConnectionType;

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

            QString stateString;

            switch (state)
            {
                case QModbusDevice::UnconnectedState:
                    stateString = "UnconnectedState";
                    break;
                case QModbusDevice::ConnectingState:
                    stateString = "ConnectingState";
                    break;
                case QModbusDevice::ConnectedState:
                    stateString = "ConnectedState";
                    break;
                case QModbusDevice::ClosingState:
                    stateString = "ClosingState";
                    break;
                default:
                    break;
            }

            SEND_TO_LOG( QString("%1 - %2").arg(objectName()).arg(stateString) );
        });
    }

    //--------------------------------------------------
    if (m_modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        if (m_modbusConnectionSettings->modbusConnectionType == Serial)
        {
            m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                m_modbusConnectionSettings->serialPortNameParameter);
            m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                m_modbusConnectionSettings->serialParityParameter);
            m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                m_modbusConnectionSettings->serialParityParameter);
            m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                m_modbusConnectionSettings->serialDataBitsParameter);
            m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                m_modbusConnectionSettings->serialStopBitsParameter);
        } else {
            m_modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter,
                m_modbusConnectionSettings->networkPortParameter);
            m_modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter,
                m_modbusConnectionSettings->networkAddressParameter);
        }

        m_modbusDevice->setTimeout(m_modbusConnectionSettings->responseTime);
        m_modbusDevice->setNumberOfRetries(m_modbusConnectionSettings->numberOfRetries);

        if (!m_modbusDevice->connectDevice())
        {
            SEND_TO_LOG( QString("%1 - Connect failed: %2")
                         .arg(objectName())
                         .arg(m_modbusDevice->errorString()) );
        }
    } else {
        m_modbusDevice->disconnectDevice();
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterHandler::readRequest(const int serverAddress, QModbusDataUnit &readDataUnit)
{
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

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();
        for (uint i = 0; i < unit.valueCount(); i++)
        {
            const QString entry = tr("Address: %1, Value: %2")
                                  .arg(unit.startAddress() + i)
                                  .arg(QString::number(unit.value(i),
                                                       unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16)
                                       );
            //ui->readValue->addItem(entry);
        }
    } else if (reply->error() == QModbusDevice::ProtocolError)
    {
        SEND_TO_LOG( QString("%1 - Read response error: %2 (Mobus exception: 0x%3)")
                     .arg(objectName())
                     .arg(reply->errorString())
                     .arg(reply->rawResult().exceptionCode(), -1, 16)
                   );
    } else {
        SEND_TO_LOG( QString("%1 - Read response error: %2 (code: 0x%3)")
                     .arg(objectName())
                     .arg(reply->errorString())
                     .arg(reply->error(), -1, 16)
                   );
    }

    reply->deleteLater();
}
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
