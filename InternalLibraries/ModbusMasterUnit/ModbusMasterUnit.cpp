#include "ModbusMasterUnit.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterUnit::ModbusMasterUnit(QObject *parent)
                 :QObject(parent),
                  m_handler ( new ModbusMasterHandler(this) )
#ifdef CIRCULAR_PROCESSING_REQUEST
                  ,m_circularTimer ( new QTimer(this) )
                  ,m_curentRequestId ( 0 )
#else
                  ,m_requestQueueSemaphore ( 10 )
#endif // CIRCULAR_PROCESSING_REQUEST
{
    setObjectName("ModbusMasterUnit");

    //-------------------------------------------
    setup( loadFile( qApp->applicationDirPath()+"/conf/modbus.conf" ) );

#ifdef CIRCULAR_PROCESSING_REQUEST
    //! После окончания паузы запустить на выполнение следующий запрос
    connect(m_circularTimer, &QTimer::timeout, [=](){

        m_circularTimer->stop();

        //! Если в конфигурации существуют корректно описанные запросы
        if(m_requestList.size() > 0)
        {
            //--------------------------------------------------
            ModbusRequest *request = m_requestList.at(m_curentRequestId);

            SEND_TO_LOG( QString("%1 - Выполнение запроса [%2]-[%3]")
                         .arg(objectName()).arg(m_curentRequestId).arg(request->objectName()) );

            //--------------------------------------------------
            m_curentRequestId++;

            if(m_curentRequestId == m_requestList.size())
            {
                m_curentRequestId = 0;
            }

            //--------------------------------------------------
            m_handler->exequteRequest(request);
        }
    });

    //! При получении сигнала о выполнении запроса
    //! Запустить таймер паузы
    connect(m_handler, &ModbusMasterHandler::exequted, [=](){
        m_circularTimer->start(PERIOD_BETWEEN_REQUEST_MS);
    });

    //! Начальный запуск опросов
    m_circularTimer->start(100);

#endif // CIRCULAR_PROCESSING_REQUES

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterUnit::~ModbusMasterUnit()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
QJsonObject ModbusMasterUnit::loadFile(const QString &fileName)
{
    QFile loadFile(fileName);

    if (!loadFile.open(QIODevice::ReadOnly))
    {
        SEND_TO_LOG( QString("%1 - ERROR (couldn't open file[%2])").arg(objectName()).arg(fileName) );
        return QJsonObject();
    }

    QByteArray fileArray = loadFile.readAll();

    QJsonParseError jsonParseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(fileArray, &jsonParseError);

    if(jsonParseError.error == QJsonParseError::ParseError::NoError )
    {
        return jsonDocument.object();
    } else
    {
        SEND_TO_LOG( QString("%1 - ERROR (Ошибка формата [%2])").arg(objectName()).arg(jsonParseError.errorString()) );
        return QJsonObject();
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::setup(const QJsonObject &confJsonObject)
{
    SEND_TO_LOG( QString("%1 - конфигурирование запущено").arg(objectName()) );

    //---------------------------------------------------
    /*
    QByteArray dataArray = QJsonDocument(confJsonObject).toJson(QJsonDocument::Indented);
    SEND_TO_LOG( QString("%1 \r\n %2").arg(objectName()).arg( dataArray.data() ) );
    */
    //---------------------------------------------------

    QJsonArray connectionsJsonArray = confJsonObject.value("connections").toArray();

    foreach (const QJsonValue &value, connectionsJsonArray)
    {
        const QJsonObject connectionJsonObject = value.toObject();

        //! Если есть признак использования - обработать
        if( connectionJsonObject.value("isUsed").toBool() )
        {
            connectionParsing(connectionJsonObject);
        }
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::connectionParsing(const QJsonObject &connectionJsonObject)
{
    const QString typeString = connectionJsonObject.value("type").toString();

    ModbusConnection modbusConnectionType = ModbusConnection::Serial;

    if(typeString == "serial")
    {
        modbusConnectionType = ModbusConnection::Serial;
    } else if(typeString == "tcp")
    {
        modbusConnectionType = ModbusConnection::Tcp;
    }

    //----------------------------------------------------------------
    const QString serialPortNameParameter       = connectionJsonObject.value("portName").toString();

    const int serialParityParameter             = static_cast<QSerialPort::Parity>(connectionJsonObject.value("parity").toInt());
    const int serialBaudRateParameter           = static_cast<QSerialPort::BaudRate>(connectionJsonObject.value("baudRate").toInt());
    const int serialDataBitsParameter           = static_cast<QSerialPort::DataBits>(connectionJsonObject.value("dataBits").toInt());
    const int serialStopBitsParameter           = static_cast<QSerialPort::StopBits>(connectionJsonObject.value("stopBits").toInt());
    //
    const QString &networkAddressParameter      = connectionJsonObject.value("networkAddress").toString();
    const int networkPortParameter              = connectionJsonObject.value("networkPort").toInt();
    //
    const int responseTime                      = connectionJsonObject.value("responseTime").toInt();
    const int numberOfRetries                   = connectionJsonObject.value("numberOfRetries").toInt();
    //
    //----------------------------------------------------------------
    ModbusConnectionSettings modbusConnectionSettings(modbusConnectionType,
                                                      //
                                                      serialPortNameParameter,
                                                      serialParityParameter,
                                                      serialBaudRateParameter,
                                                      serialDataBitsParameter,
                                                      serialStopBitsParameter,
                                                      //
                                                      networkAddressParameter,
                                                      networkPortParameter,
                                                      //
                                                      responseTime,
                                                      numberOfRetries);

    //----------------------------------------------------------------
    QJsonArray devicesJsonArray                 = connectionJsonObject.value("devices").toArray();

    foreach (const QJsonValue &value, devicesJsonArray)
    {
        const QJsonObject deviceJsonObject = value.toObject();

        //! Если есть признак использования - обработать
        if( deviceJsonObject.value("isUsed").toBool() )
        {
            deviceParsing(modbusConnectionSettings, deviceJsonObject);
        }
    }
#ifdef CIRCULAR_PROCESSING_REQUEST
    //! Старт перебора запросов
    m_circularTimer->start(PERIOD_BETWEEN_REQUEST_MS);
#endif // CIRCULAR_PROCESSING_REQUES
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::deviceParsing(const ModbusConnectionSettings &modbusConnectionSettings,
                                     const QJsonObject &deviceJsonObject)
{
    const quint16 serverAddress                 = static_cast<quint16>(deviceJsonObject.value("serverAddress").toInt());
    const QString title                         = deviceJsonObject.value("title").toString();
    const QModbusPdu::FunctionCode functionCode = static_cast<QModbusPdu::FunctionCode>(deviceJsonObject.value("functionCode").toInt());

    QJsonArray registersJsonArray               = deviceJsonObject.value("registers").toArray();

    QList< std::tuple<int, QString, QString> > registerList;

    foreach (const QJsonValue &value, registersJsonArray)
    {
        const QJsonObject registerJsonObject = value.toObject();

        const int id          = registerJsonObject.value("id").toInt();
        const QString name    = registerJsonObject.value("name").toString();
        const QString title   = registerJsonObject.value("title").toString();

        std::tuple<int, QString, QString> reg = std::make_tuple(id, name, title);

        registerList.append( reg );
    }

    //--------------------------------------------
    ModbusRequest *modbusRequest = new ModbusRequest(modbusConnectionSettings,
                                                     serverAddress,
                                                     functionCode,                                                
                                                     registerList,
#ifndef CIRCULAR_PROCESSING_REQUEST
                                                     1000,
#endif // CIRCULAR_PROCESSING_REQUEST
                                                     this);

#ifndef CIRCULAR_PROCESSING_REQUEST
    connect(modbusRequest, &ModbusRequest::wantExecuteQuery,
            this, &ModbusMasterUnit::executeQuery);
#else
    m_requestList.append(modbusRequest);
#endif // CIRCULAR_PROCESSING_REQUEST
}
//------------------------------------------------------------------------------------
//!
#ifndef CIRCULAR_PROCESSING_REQUEST
void ModbusMasterUnit::executeQuery(ModbusRequest *request)
{

    SEND_TO_LOG( QString("%1 - Постановка запроса в очередь на выполнение [%2]")
                 .arg(objectName()).arg(request->objectName()) );

    //------------------------------------------------------------
    if(m_requestQueueSemaphore.available() == 0)
    {
        SEND_TO_LOG( QString("%1 - Error(Очередь переполнена").arg(objectName()) );
        return;
    }

    m_requestQueueSemaphore.acquire();
    m_requestQueue.enqueue(request);

    //------------------------------------------------------------
    //------------------------------------------------------------
    //! Из другого потока
    //------------------------------------------------------------
    SEND_TO_LOG( QString("%1 - Выемка запроса из очереди на выполнение [%2]")
                 .arg(objectName()).arg(request->objectName()) );

    ModbusRequest *requestFromQueue = m_requestQueue.dequeue();

    m_handler->reconnect(requestFromQueue->connectionSettings());

    m_requestQueueSemaphore.release();
}
#endif // CIRCULAR_PROCESSING_REQUEST
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::startWorkInAThread(const ModbusConnectionSettings &modbusConnectionSettings)
{
    ModbusConnectionController *modbusConnectionController
            = new ModbusConnectionController(modbusConnectionSettings);
//    connect(modbusConnectionController, &ModbusConnectionController::resultReady,
//            this, &MyObject::handleResults);

    connect(modbusConnectionController, &ModbusConnectionController::finished,
            modbusConnectionController, &QObject::deleteLater);
    modbusConnectionController->start();
}

