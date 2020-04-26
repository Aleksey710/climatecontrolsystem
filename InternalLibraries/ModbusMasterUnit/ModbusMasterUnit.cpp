#include "ModbusMasterUnit.h"

//------------------------------------------------------------------------------------
int ModbusMasterUnit::m_curentRequestId = 0 ;
//------------------------------------------------------------------------------------
//!
ModbusMasterUnit::ModbusMasterUnit(QObject *parent)
                 :QObject(parent),
                  //m_modbusThreadController ( new ModbusThreadController(this) )
                  m_handler ( new ModbusMasterHandler(this) )
//-------------------------------------------
#ifdef CIRCULAR_PROCESSING_REQUEST
                  ,m_requestPeriodTimer ( new QTimer(this) )
//                  ,m_curentRequestId ( 0 )
#else
                  ,m_requestQueueSemaphore ( 10 )
#endif // CIRCULAR_PROCESSING_REQUEST
//-------------------------------------------
{
    setObjectName("ModbusMasterUnit");

    setup( loadFile( qApp->applicationDirPath()+"/conf/modbus.json" ) );

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterUnit::~ModbusMasterUnit()
{
//    while (!m_requestList.isEmpty())
//    {
//        delete m_requestList.takeFirst();
//    }

    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//! Обработчик окончания конфигурирования
void ModbusMasterUnit::setupEndHandler()
{
    SEND_TO_LOG( QString("%1 - конфигурирование завершено").arg(objectName()) );

//    qDebug() << "ModbusMasterUnit::setupEndHandler" << m_curentRequestId << m_requestList.size();

#ifdef CIRCULAR_PROCESSING_REQUEST

    //! В начале каждого периода запускать начало опросов
    connect(m_requestPeriodTimer, &QTimer::timeout,
            this, &ModbusMasterUnit::excuteNextRequest);
    m_requestPeriodTimer->setObjectName("m_requestPeriodTimer");

    //! При получении сигнала о выполнении запроса
    connect(m_handler, &ModbusMasterHandler::exequted,
    //connect(m_modbusThreadController, &ModbusThreadController::exequted,
            this, &ModbusMasterUnit::exequtedHandler);

    //! Запустить таймер циклов
    m_requestPeriodTimer->start(PERIOD_REQUEST_MS);
    m_elapsedTimeRoutins.invalidate();
    m_elapsedTimeBetween.start();
    m_elapsedTimePeriod.start();

#endif // CIRCULAR_PROCESSING_REQUES
}
//------------------------------------------------------------------------------------
//! Обработчик окончания выполнения запроса
void ModbusMasterUnit::exequtedHandler()
{
    //! Если не все запросы цикла были выполнены
    if(m_curentRequestId < m_requestList.size())
    {
        qint64 nextRequstTime = PERIOD_BETWEEN_REQUEST_MS;
        if ( m_elapsedTimeRoutins.isValid() )
        {
            qint64 exequtedTime = m_elapsedTimeRoutins.elapsed();
            nextRequstTime = PERIOD_BETWEEN_REQUEST_MS - exequtedTime;
            if ( nextRequstTime < 5 )
            {
                    SEND_TO_LOG(
                        QString("!!!! excuteNextRequest - veri long exequted %1 ms (next req time %2 ms replaced by %3 ms)"
                                  ).arg(exequtedTime).arg(nextRequstTime).arg(PERIOD_BETWEEN_REQUEST_MS) );
                    nextRequstTime = PERIOD_BETWEEN_REQUEST_MS;
            }
            m_elapsedTimeRoutins.invalidate();
        } else {
            SEND_TO_LOG( QString("!!!!ModbusMasterUnit::exequtedHandler - elapsedTime invalid)") );
        }

        //! Запустить таймер паузы между запросами,
        //! по окнчании которого - запустить на выполнение следующий запрос
        QTimer::singleShot( nextRequstTime, this, &ModbusMasterUnit::excuteNextRequest );
        //QTimer::singleShot( PERIOD_BETWEEN_REQUEST_MS, this, &ModbusMasterUnit::excuteNextRequest );
    }
}
//------------------------------------------------------------------------------------
#ifdef CIRCULAR_PROCESSING_REQUEST
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::excuteNextRequest()
{
    QString periodStr("");
    if ( sender() != nullptr )
    {
        periodStr = periodStr.number(m_elapsedTimePeriod.restart());
    }

    m_elapsedTimeRoutins.start();


    SEND_TO_LOG( QString("%1 - %2 %3===================================================== excuteNextRequest")
                    .arg(objectName())
                    .arg(m_elapsedTimeBetween.restart())
                    .arg(periodStr) );

    //--------------------------------------------------
    if(m_curentRequestId >= m_requestList.size())
    {
        m_curentRequestId = 0;
    }

    //--------------------------------------------------
    ModbusRequest *request = m_requestList.at(m_curentRequestId);

    SEND_TO_LOG( QString("%1 - Выполнение запроса [%2]-[%3]")
                 .arg(objectName()).arg(m_curentRequestId).arg(request->objectName()) );

    //--------------------------------------------------
    m_curentRequestId++;

    //--------------------------------------------------
    m_handler->exequteRequest(request);
    //m_modbusThreadController->exequteRequest(request);
}
#endif // CIRCULAR_PROCESSING_REQUES
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

    //! Обработчик окончания конфигурирования
    setupEndHandler();
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
#ifdef __arm__
    // Только под платформу ARM
    const QString serialPortNameParameter = QString("/dev/ttyAMA0");
#else
    const QString serialPortNameParameter = connectionJsonObject.value("portName").toString();
#endif // __arm__

    const char serialParityParameter    = connectionJsonObject.value("parity").toString().toLatin1().at(0);
    const int serialBaudRateParameter   = connectionJsonObject.value("baudRate").toInt();
    const int serialDataBitsParameter   = connectionJsonObject.value("dataBits").toInt();
    const int serialStopBitsParameter   = connectionJsonObject.value("stopBits").toInt();
    //
    const QString networkAddressParameter = connectionJsonObject.value("networkAddress").toString();
    const int networkPortParameter      = connectionJsonObject.value("networkPort").toInt();
    //
    const int responseTime              = connectionJsonObject.value("responseTime").toInt();
    const int numberOfRetries           = connectionJsonObject.value("numberOfRetries").toInt();
    //
    //----------------------------------------------------------------
    const ModbusConnectionSettings modbusConnectionSettings(
        modbusConnectionType,
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
    const QJsonArray devicesJsonArray            = connectionJsonObject.value("devices").toArray();

    foreach (const QJsonValue &value, devicesJsonArray)
    {
        const QJsonObject deviceJsonObject = value.toObject();

        //! Если есть признак внешнего датчика
        if( deviceJsonObject.value("isExternal").toBool() )
        {
            //! Проверить режим работы
            //! Використання датчикiв температри БВВ true(1) або false(0) - використання окремих датчикiв.
            ScriptObject *scriptObject = ScriptUnit::getScriptObject("settings.temp.useBVV");

            if(scriptObject)
            {
                double value = scriptObject->data();

                //! Если режим работы регламентирует использование
                if(value == 0)
                {
                    SEND_TO_LOG( QString("%1 - Режим использования внешнего датчика (use BVV)").arg(objectName()) );
                    deviceParsing(modbusConnectionSettings, deviceJsonObject);
                }
            }

        } else
        {
            deviceParsing(modbusConnectionSettings, deviceJsonObject);
        }
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::deviceParsing(const ModbusConnectionSettings &modbusConnectionSettings,
                                     const QJsonObject &deviceJsonObject)
{
    const quint16 serverAddress  = static_cast<quint16>(deviceJsonObject.value("serverAddress").toInt());
    const QString title          = deviceJsonObject.value("title").toString();
    const int functionCode       = deviceJsonObject.value("functionCode").toInt();

    const QJsonArray registersJsonArray = deviceJsonObject.value("registers").toArray();

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
                                                     this
                                                     );

#ifndef CIRCULAR_PROCESSING_REQUEST
    connect(modbusRequest, &ModbusRequest::wantExecuteQuery,
            this, &ModbusMasterUnit::executeQuery);
#else
    //qDebug() << "ModbusMasterUnit::deviceParsing m_requestList.size1" << m_requestList.size();
    m_requestList.append(modbusRequest);
    //qDebug() << "ModbusMasterUnit::deviceParsing m_requestList.size2" << m_requestList.size();
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

