#include "ModbusMasterConfigurator.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterConfigurator::ModbusMasterConfigurator()
{
    m_configuratorName = "ModbusMasterConfigurator";

    //-------------------------------------------------------------------
    m_dpdTopicName = unitItem->parentItem()->topicName();

    //-------------------------------------------------------------------
    using namespace std::placeholders;

    //! Этапы конфигурирования

    m_stepConfigList.append( StepConfig(DbInitQuery::selectModbusConnectionsQueryString(m_dpdTopicName),
                                        std::bind(&MqttModbusMasterConfigurator::sqlResultHandler, this, _1),
                                        "Инициализация линий (порты RS485)") );

    m_stepConfigList.append( StepConfig(DbInitQuery::selectModbusDevicesQueryString(m_dpdTopicName),
                                        std::bind(&MqttModbusMasterConfigurator::sqlResultSetupDeviceHandler, this, _1),
                                        "Инициализация устройств на линии") );

    m_stepConfigList.append( StepConfig(DbInitQuery::selectModbusRegistersQueryString(m_dpdTopicName),
                                        std::bind(&MqttModbusMasterConfigurator::sqlResultSetupRegistersHandler, this, _1),
                                        "Инициализация регистров устройств") );

    //! Запустить конфигурирование
    configure();

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("%1 - конфигурирование окончено").arg(m_configuratorName) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterConfigurator::~ModbusMasterConfigurator()
{
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::sqlResultHandler(QSqlQuery &query)
{
    int modbus_type_id      = query.record().indexOf("modbus_type");
    int title_id            = query.record().indexOf("title");
    int uart_port_name_id   = query.record().indexOf("uart_port_name");
    int topic_name_id       = query.record().indexOf("topic_name");
    int baud_rate_type_id   = query.record().indexOf("baud_rate_type");
    int parity_type_id      = query.record().indexOf("parity_type");
    int data_bits_type_id   = query.record().indexOf("data_bits_type");
    int stop_bits_type_id   = query.record().indexOf("stop_bits_type");
    int ip_address_id       = query.record().indexOf("ip_address");
    int tcp_port_id         = query.record().indexOf("tcp_port");

    MqttModbusConnectionTopicItem *connectionItem;

    while (query.next())
    {
        QString modbusType = query.value(modbus_type_id).toString();
        QString title      = query.value(title_id).toString();
        QString topicName  = query.value(topic_name_id).toString();

        //qDebug() << "Modbus connection" << modbusType << title << topicName;
        //-------------------------------------------------------
        if(modbusType == QStringLiteral("RTU")   ||
           modbusType == QStringLiteral("ASCII") ||
           modbusType == QStringLiteral("ISI"))
        {
            QString uartPortName  = query.value(uart_port_name_id).toString();
            int baudRate          = query.value(baud_rate_type_id).toInt();
            char parity           = query.value(parity_type_id).toString().toLatin1().at(0);
            int dataBits          = query.value(data_bits_type_id).toInt();
            int stopBits          = query.value(stop_bits_type_id).toString().toInt();

//            qDebug() << modbusType << title << topicName
//                     << uartPortName << baudRate << parity << dataBits << stopBits;

            connectionItem = new MqttModbusSerialConnectionTopicItem(modbusType,
                                                                     topicName,
                                                                     uartPortName,
                                                                     baudRate,
                                                                     parity,
                                                                     dataBits,
                                                                     stopBits,
                                                                     m_unitItem);

        } else if(modbusType == QStringLiteral("TCP") )
        {
            QString ipAddress  = query.value(ip_address_id).toString();
            int tcpPort    = query.value(tcp_port_id).toInt();

//            qDebug() << modbusType << title << topicName
//                     << ipAddress << tcpPort;

            connectionItem = new MqttModbusTcpConnectionTopicItem(topicName,
                                                                  title,
                                                                  ipAddress,
                                                                  tcpPort,
                                                                  m_unitItem);
        } else
        {
            connectionItem = Q_NULLPTR;

            SEND_TO_LOG( QString("%1 - Не известный тип Modbus [%2]").arg(m_configuratorName).arg(modbusType) );
        }

        //-------------------------------------------
        if(connectionItem)
        {
            m_connectionsItemList.insert(topicName, connectionItem);

            m_unitItem->appendChildren(connectionItem);
        }
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::sqlResultSetupDeviceHandler(QSqlQuery &query)
{
    int modbus_connection_topic_name_id  = query.record().indexOf("modbus_connection_topic_name");
    int device_id_id                     = query.record().indexOf("device_id");
    int device_topic_name_id             = query.record().indexOf("device_topic_name");
    int slave_address_id                 = query.record().indexOf("slave_address");

    while (query.next())
    {
        QString modbusConnectionTopicName  = query.value(modbus_connection_topic_name_id).toString();
        int deviceId                       = query.value(device_id_id).toInt();
        QString deviceTopicName            = query.value(device_topic_name_id).toString();
        quint16 slaveAddress               = query.value(slave_address_id).toString().toUShort();

        //qDebug() << "Modbus device" << modbusConnectionTopicName << deviceTopicName << slaveAddress ;

        MqttModbusConnectionTopicItem *connectionItem = static_cast<MqttModbusConnectionTopicItem*>
                ( m_connectionsItemList.value(modbusConnectionTopicName, Q_NULLPTR) );

        if(!connectionItem)
        {
            SEND_TO_LOG( QString("%1 - connectionItem [%2] - не найден").arg(m_configuratorName).arg(modbusConnectionTopicName) );
            continue;
        }

        MqttModbusDeviceTopicItem *deviceItem = new MqttModbusDeviceTopicItem(deviceTopicName,
                                                                              slaveAddress,
                                                                              modbusConnectionTopicName,
                                                                              connectionItem);

        QString deviceFullTopicName = deviceItem->fullTopicName();

        MqttTopicPublisher *devicePublisher = m_mqttClient->createPublisher(deviceFullTopicName);

        //! Назначить обработчику устройства публикатор
        deviceItem->setPublisher(devicePublisher);

        connectionItem->appendChildren(deviceItem);

        //!-----------------------------------------------------
        m_devicesItemList.insert(deviceId, deviceItem);

        //!-----------------------------------------------------
        if(connectionItem)
        {
            ModbusMasterConnectionController *modbusMasterConnectionController = connectionItem->modbusMasterConnectionController();

            //! Обработка получения новых данных при опросе
            QObject::connect(modbusMasterConnectionController, &ModbusMasterConnectionController::newData,
                             //! Передавать по значению!!! Иначе не приходят данные от опросников.
                             [deviceItem, slaveAddress](const ModbusData &modbusData, int slAddr){

                //! Если результат modbus запроса пришел с адресом "нужного" устройства
                if(slaveAddress == slAddr)
                {
                    //! Передать данные на обработку в устройство
                    deviceItem->setModbusData(modbusData);
                }
            });
        }
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::sqlResultSetupRegistersHandler(QSqlQuery &query)
{
    int connection_topic_name_id  = query.record().indexOf("connection_topic_name");
    int connection_title_id       = query.record().indexOf("connection_title");
    //-------------------------------------------
    int device_id_id              = query.record().indexOf("device_id");
    int device_topic_name_id      = query.record().indexOf("device_topic_name");
    int device_title_id           = query.record().indexOf("device_title");
    int device_slave_address_id   = query.record().indexOf("device_slave_address");
    //-------------------------------------------
    int requester_id_id           = query.record().indexOf("requester_id");    
    int period_ms_id              = query.record().indexOf("period_ms");
    int timeout_ms_id             = query.record().indexOf("timeout_ms");
    int function_id               = query.record().indexOf("function");
    int start_address_id          = query.record().indexOf("start_address");
    //-------------------------------------------
    int register_number_id        = query.record().indexOf("register_number");
    int register_topic_name_id    = query.record().indexOf("register_topic_name");
    int register_title_id         = query.record().indexOf("register_title");

    while (query.next())
    {
        QString connection_topic_name = query.value(connection_topic_name_id).toString();
        QString connection_title      = query.value(connection_title_id).toString();
        //-------------------------------------------
        int device_id                 = query.value(device_id_id).toInt();
        QString device_topic_name     = query.value(device_topic_name_id).toString();
        QString device_title          = query.value(device_title_id).toString();
        int device_slave_address      = query.value(device_slave_address_id).toInt();
        //-------------------------------------------
        int requester_id              = query.value(requester_id_id).toInt();
        int period_ms                 = query.value(period_ms_id).toInt();
        int timeout_ms                = query.value(timeout_ms_id).toInt();
        int function                  = query.value(function_id).toInt();
        int start_address             = query.value(start_address_id).toInt();

        //MODBUS_FUNCTIONS funktionCode = static_cast<MODBUS_FUNCTIONS>(attributeValue(configNode, "FunktionCode", "3").toInt());

        Requester requester = m_requestersList.value(requester_id, Requester());

        if(requester.isEmpty)
        {
            requester = Requester(requester_id,
                                  period_ms,
                                  timeout_ms,
                                  function,
                                  start_address);

//            qDebug() << "Requester:"
//                     << requester_id
//                     << period_ms
//                     << timeout_ms
//                     << function
//                     << start_address ;

            m_device_requesters.insert(device_id, requester_id);

            m_requestersList.insert(requester_id, requester);
        }

        //-------------------------------------------
        quint16 register_number       = static_cast<quint16>(query.value(register_number_id).toUInt());
        QString register_topic_name   = query.value(register_topic_name_id).toString();
        QString register_title        = query.value(register_title_id).toString();
        //-------------------------------------------
        //qDebug() << "Modbus register" << connection_topic_name << device_topic_name << requester_id << register_number ;

        //qDebug() << "deviceFullTopicName" << deviceFullTopicName;

        ModbusDeviceItem *deviceItem =
                static_cast<ModbusDeviceItem*>(m_devicesItemList.value(device_id, Q_NULLPTR));

        if(deviceItem)
        {
            QString errorStringTitle = QString("DPD[%1]->%2->%3->%4")
                                         .arg(m_dpdTopicName)                   // 1
                                         .arg(QString("line(%1)[%2]")
                                              .arg(connection_title)            // 1
                                              .arg(connection_topic_name)       // 2
                                              )
                                         .arg(QString("device(%1)addr(%2)[%3]")
                                              .arg(device_title)                // 1
                                              .arg(device_slave_address)        // 2
                                              .arg(device_topic_name)           // 3
                                              )
                                         .arg(QString("register(%1)addr(%2)[%3]")
                                              .arg(register_title)              // 1
                                              .arg(register_number)             // 2
                                              .arg(register_topic_name)         // 3
                                              )
                                         ;

            //----------------------------------------------
            ModbusRegisterItem *registerTopicItem = new ModbusRegisterItem(register_topic_name,
                                                                           register_number,
                                                                           errorStringTitle,
                                                                           deviceItem);

            QString registerFullTopicName = registerTopicItem->fullTopicName();

            MqttTopicPublisher *registerPublisher = m_mqttClient->createPublisher(registerFullTopicName);

            //! Назначить обработчику публикатор
            registerTopicItem->setPublisher(registerPublisher);

            //----------------------------------------------
            m_requesterId_register.insert(requester_id, register_number);

            //----------------------------------------------
            //! Добавить устройству регистр
            deviceItem->addMqttModbusRegisterTopicItem(register_number, registerTopicItem);
        } else
        {
            QString deviceFullTopicName = m_unitItem->fullTopicName()+"/"+connection_topic_name+"/"+device_topic_name;

            SEND_TO_LOG( QString("%1 - устройство [%2] не заявлено - ERROR")
                         .arg(m_configuratorName).arg(deviceFullTopicName) );
        }
    }

    createModbusRequesters();
    //qDebug() << "m_registerInRequesters" << m_registerInRequesters;
    //qDebug() << m_device_requesters;
}
//------------------------------------------------------------------------------------
//!
void MqttModbusMasterConfigurator::createModbusRequesters()
{
    QHashIterator<int, ModbusDeviceItem*> i_devicesItemList(m_devicesItemList);

    //! Перебрать устройства
    while (i_devicesItemList.hasNext())
    {
        i_devicesItemList.next();
        //----------------------------------------
        int deviceId                      = i_devicesItemList.key();
        ModbusDeviceItem *deviceTopicItem = i_devicesItemList.value();

        //----------------------------------------
        if( !deviceTopicItem->hasChildren() )
        {
            SEND_TO_LOG( QString("%1 - у устройства [%2] не заявлено регистров. Пропущено")
                         .arg(m_configuratorName)
                         .arg(deviceTopicItem->fullTopicName()) );
            continue;
        }

        //----------------------------------------
        QList<int> requestersIdList = m_device_requesters.values(deviceId);

        int requestersIdListSize = requestersIdList.size();

        if(requestersIdListSize == 0)
        {
            SEND_TO_LOG( QString("%1 - у устройства [%2] не заявлено опросников. Пропущено")
                         .arg(m_configuratorName)
                         .arg(deviceTopicItem->fullTopicName()) );
            continue;
        }

        //----------------------------------------
        //! Перебрать опросники регистра
        for(int i = 0; i < requestersIdList.size() ; ++i)
        {
            int requesterId = requestersIdList.at(i);

            Requester requester = m_requestersList.value(requesterId);

            //----------------------------------------
            QList<quint16> registersInRequester  = m_requesterId_register.values(requesterId);

            std::sort(registersInRequester.begin(), registersInRequester.end());

            //! +1 - включительно
            int number = registersInRequester.last() - registersInRequester.first() + 1;

            //----------------------------------------
            if(number > 250)
            {
                number = 250;
                SEND_TO_LOG( QString("%1 - Заявлено больше 250 регистров в опроснике устройства [%2]")
                             .arg(m_configuratorName)
                             .arg(deviceTopicItem->fullTopicName()) );
            }
            //----------------------------------------
            MODBUS_FUNCTIONS function = static_cast<MODBUS_FUNCTIONS>(requester.function);

            //----------------------------------------
            //! Создать запрос
            ModbusRequest modbusRequest(/*requester.start_address,*/
                                        registersInRequester.first(),
                                        number,
                                        function,
                                        deviceTopicItem->modbusSlaveAddress(),
                                        requester.timeout_ms);

            ModbusConnectionItem *connectionItem = dynamic_cast<ModbusConnectionItem*>(deviceTopicItem->parentItem());

            ModbusMasterConnectionController *connectionController = connectionItem->modbusMasterConnectionController();

            //! Добавить запрос в контроллер линии
            connectionController->addRequester(modbusRequest, requester.period_ms);
        }
    }
}
//------------------------------------------------------------------------------------
//!
