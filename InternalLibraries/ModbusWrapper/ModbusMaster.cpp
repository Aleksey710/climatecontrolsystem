#include "ModbusMaster.h"
//------------------------------------------------------------------------------------
//!
ModbusMaster::ModbusMaster(const QString &coreType,
                           const ModbusConnectionAddress &modbusConnectionAddress,
                           QObject *parent)
             :ModbusPartner(coreType, modbusConnectionAddress, parent),
              m_notFoundSerialDeviceErrorCount ( 0 )
{
    setObjectName(QString("ModbusMaster[%1]").arg(coreType));

    //SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
ModbusMaster::~ModbusMaster()
{
    //SEND_TO_LOG( QString("%1 - удален (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
ModbusData ModbusMaster::executeRequest(const ModbusRequest &modbusRequest)
{
    //qDebug() << "ModbusMaster::executeRequest" << m_modbusCore;

    if(m_modbusCore->modbus() == nullptr)
    {
        //! Переподключиться
        reinit();

        //-------------------------------------------------

        if(m_modbusCore->modbus() == nullptr)
        {
            return ModbusData(modbusRequest.address,
                              modbusRequest.number,
                              errno);
        }
    } else
    {
        //! Обнулить счетчик неудачных подключений
        m_notFoundSerialDeviceErrorCount = 0;
    }

    //-------------------------------------------------
    switch (modbusRequest.funk)
    {
        case NONE_FUNCTION:
            break;
        case READ_COILS:
        case READ_DISCRETE_INPUTS:
        case READ_HOLDING_REGISTERS:
        case READ_INPUT_REGISTERS:
        case READ_EXCEPTION_STATUS:
        {
            return read(modbusRequest.address,
                        modbusRequest.number,
                        modbusRequest.funk,
                        modbusRequest.slaveAddress,
                        modbusRequest.responseTimeout_ms);
        }
            break;
        case WRITE_SINGLE_COIL:
        case WRITE_SINGLE_REGISTER:
        case WRITE_MULTIPLE_COILS:
        case WRITE_MULTIPLE_REGISTERS:
        {
            write(modbusRequest.address,
                  modbusRequest.number,
                  modbusRequest.funk,
                  modbusRequest.slaveAddress,
                  modbusRequest.responseTimeout_ms);
        }
            break;
        case REPORT_SLAVE_ID:
            break;
        case MASK_WRITE_REGISTER:
            break;
        case WRITE_AND_READ_REGISTERS:
            break;
        default:
            break;
    }

    return ModbusData(modbusRequest.address, modbusRequest.number);
}
//------------------------------------------------------------------------------------
//!
ModbusData ModbusMaster::read(int addr,
                              int nb,
                              MODBUS_FUNCTIONS funk,
                              int slaveAddress,
                              uint32_t responseTimeout_ms)
{    
    //SEND_TO_LOG( QString("%1 - read (%2)").arg(objectName()).arg( (quint64)thread() ) );

    ModbusData data(addr, nb);

    if(slaveAddress != MODBUS_TCP_SLAVE)
    {
        modbus_set_slave(m_modbusCore->modbus(), slaveAddress);
    }

    //! Задание времени ожидания в секундах и микросекундах( ms = mu*1000 )
    modbus_set_response_timeout(m_modbusCore->modbus(), 0, responseTimeout_ms*1000);

    //modbus_error_recovery_mode error_recovery = MODBUS_ERROR_RECOVERY_NONE;
    //modbus_error_recovery_mode error_recovery = MODBUS_ERROR_RECOVERY_LINK;
    modbus_error_recovery_mode error_recovery = MODBUS_ERROR_RECOVERY_PROTOCOL;

    modbus_set_error_recovery(m_modbusCore->modbus(), error_recovery);

    int rc = -1;

//    QMutexLocker locker(&m_mutex);

    switch (funk)
    {
        case MODBUS_FUNCTIONS::NONE_FUNCTION:
        {            
            return data;
        }
            break;
        case MODBUS_FUNCTIONS::READ_COILS:
        {
            uint8_t dest8[nb];
            rc = modbus_read_bits(m_modbusCore->modbus(), addr, nb, dest8);

            if (rc == -1)
            {
                data = ModbusData::fromArray<uint8_t>(dest8, addr, nb, errno);
            } else
            {
                data = ModbusData::fromArray<uint8_t>(dest8, addr, nb, 0);
            }
        }
            break;
        case MODBUS_FUNCTIONS::READ_DISCRETE_INPUTS:
        {
            uint8_t dest8[nb];
            rc = modbus_read_input_bits(m_modbusCore->modbus(), addr, nb, dest8);

            if (rc == -1)
            {
                data = ModbusData::fromArray<uint8_t>(dest8, addr, nb, errno);
            } else
            {
                data = ModbusData::fromArray<uint8_t>(dest8, addr, nb, 0);
            }
        }
            break;
        case MODBUS_FUNCTIONS::READ_HOLDING_REGISTERS:
        {
            //qDebug()<< "ModbusMaster::read response_timeout" << m_modbusCore->modbus()->response_timeout.tv_usec;

            if(m_modbusCore->modbus()->backend->backend_type == _MODBUS_BACKEND_TYPE_ISI)
            {
                //----------------------
                /* После отладки перенести в парсер, чтоб отображалось в конфиге! */
                const int RESPONSE_TIMEOUT_ISI__MS = 300;
                //! Задание времени ожидания в секундах и микросекундах( ms = mu*1000 )
                //! Для ИСИ отдельно, мимо конфигурации (все равно он по другому не работает)
                modbus_set_response_timeout(m_modbusCore->modbus(), 0, RESPONSE_TIMEOUT_ISI__MS*1000);
                //----------------------
                // 144 (0x90)

                //! Фактически запрашивается 72, но последние 8(признак снижения сопротивления)
                //! фактически соответствуют 16
                //! срабатывания как по мануалу D0-D15 (264-295 байт)

                //! По этому делаем запас для совместимости по передаваемым далее регистрам
                //const int responseSize = 72; // 72*4 = 288 байт данных
                const int responseSize = 80; // 80*4 = 320 байт данных

                uint16_t dest16[responseSize];

                memset(dest16, 0, sizeof(dest16));

                //! Запрашивается один регистр (0x01), приходит responseSize
                //! Подготовить в опроснике соответствующее количество регистров
                rc = modbus_read_registers(m_modbusCore->modbus(), addr, 0x01, dest16);

                //----------------------
                auto convert = [](uint16_t *source, uint16_t *h, uint16_t *l){
                    // старший байт (сдвинуть старшие вниз)
                    *h = (*source) >> 8;
                    // младший байт (обнулить старшие)
                    *l = (*source) & 0xFF;
                };

                //---------------------|--------------|-------------|
                //              source |        ->l   |        ->h  |
                convert( &(dest16[71]), &(dest16[78]), &(dest16[79]) );
                convert( &(dest16[70]), &(dest16[76]), &(dest16[77]) );
                convert( &(dest16[69]), &(dest16[74]), &(dest16[75]) );
                convert( &(dest16[68]), &(dest16[72]), &(dest16[73]) );
                convert( &(dest16[67]), &(dest16[70]), &(dest16[71]) );
                convert( &(dest16[66]), &(dest16[68]), &(dest16[69]) );
                convert( &(dest16[65]), &(dest16[66]), &(dest16[67]) );
                convert( &(dest16[64]), &(dest16[64]), &(dest16[65]) );
                //---------------------------------------------------

                if (rc == -1)
                {
                    data = ModbusData::fromArray<uint16_t>(dest16, 0, responseSize, errno);
                } else
                {
                    data = ModbusData::fromArray<uint16_t>(dest16, 0, responseSize, 0);
                }
            } else
            {
                uint16_t dest16[nb];
                rc = modbus_read_registers(m_modbusCore->modbus(), addr, nb, dest16);

                //qDebug() << "ModbusMaster::read" << rc << errno << QString(modbus_strerror(errno));

                if (rc == -1)
                {
                    data = ModbusData::fromArray<uint16_t>(dest16, addr, nb, errno);
                } else
                {
                    data = ModbusData::fromArray<uint16_t>(dest16, addr, nb, 0);
                }
            }
        }
            break;
        case MODBUS_FUNCTIONS::READ_INPUT_REGISTERS:
        {
            uint16_t dest16[nb];
            rc = modbus_read_input_registers(m_modbusCore->modbus(), addr, nb, dest16);

            if (rc == -1)
            {
                data = ModbusData::fromArray<uint16_t>(dest16, addr, nb, errno);
            } else
            {
                data = ModbusData::fromArray<uint16_t>(dest16, addr, nb, 0);
            }
        }
            break;
        default:            
            break;
    }

    if (rc == -1)
    {
        QString connectionName;

        if(m_modbusConnectionAddress.type == TCP)
        {
            connectionName = QString("%1:%2")
                             .arg(m_modbusConnectionAddress.ip)
                             .arg(m_modbusConnectionAddress.port);
        } else
        {
            connectionName = m_modbusConnectionAddress.device;
        }

        //----------------------------------------------
        /*
        //! повторение MqttModbusDeviceTopicItem::setModbusData
        SEND_TO_LOG( QString("%1(%2 slave: 0x%3) - %4")
                     .arg(objectName())
                     .arg(connectionName)
                     .arg(slaveAddress, 0, 16)
                     .arg(modbus_strerror(errno)) );

        data.stateError = errno;
        */
        //----------------------------------------------
        //! Для переподключения        
        if(m_modbusConnectionAddress.type == TCP)
        {
            //! Переподключиться
            reinit();
        }
    }

    return data;
}
//------------------------------------------------------------------------------------
//!
void ModbusMaster::write(int addr,
                         int nb,
                         MODBUS_FUNCTIONS funk,
                         int slaveAddress,
                         uint32_t responseTimeout_ms)
{

    QMutexLocker locker(&m_mutex);

    Q_UNUSED (addr);
    Q_UNUSED (nb);
    Q_UNUSED (funk);
    Q_UNUSED (responseTimeout_ms);

    if(slaveAddress != MODBUS_TCP_SLAVE)
    {
        modbus_set_slave(m_modbusCore->modbus(), slaveAddress);
    }
/*
    dataArray.fill(0, nb);

    return dataArray;
    */
}


