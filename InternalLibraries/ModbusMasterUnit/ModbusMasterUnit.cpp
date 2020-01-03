#include "ModbusMasterUnit.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterUnit::ModbusMasterUnit(QObject *parent)
                 :QObject(parent),
                  m_handler ( new ModbusMasterHandler(this) )
{
    setObjectName("ModbusMasterUnit");
    //-------------------------------------------

    setup( loadFile( qApp->applicationDirPath()+"/conf/modbus.conf" ) );


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
        connectionParsing(connectionJsonObject);
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
        deviceParsing(modbusConnectionSettings, deviceJsonObject);
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::deviceParsing(const ModbusConnectionSettings &modbusConnectionSettings,
                                     const QJsonObject &deviceJsonObject)
{
    const int addr          = deviceJsonObject.value("addr").toInt();
    const QString title     = deviceJsonObject.value("title").toString();
    const int funktion      = static_cast<QModbusPdu::FunctionCode>(deviceJsonObject.value("funktion").toInt());

    QJsonArray registersJsonArray   = deviceJsonObject.value("registers").toArray();

    QList<int> addressRegList;

    foreach (const QJsonValue &value, registersJsonArray)
    {
        const QJsonObject registerJsonObject = value.toObject();

        const int id          = registerJsonObject.value("id").toInt();
        addressRegList.append(id);

        const QString name    = registerJsonObject.value("name").toString();
        const QString title   = registerJsonObject.value("title").toString();

        ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);
        if(scriptObject)
        {
            SEND_TO_LOG( QString("%1 - modbus register connected [%2])")
                         .arg(objectName()).arg(name) );

    //        connect(scriptObject, &ScriptObject::dataChanged, [=](){
    //            label->setText(QString("%1").arg(scriptObject->data()));
    //        });
        } else
        {
            SEND_TO_LOG( QString("%1 - ERROR (У регистра нет назначения [%2])")
                         .arg(objectName()).arg(name) );
        }
    }

    std::sort(addressRegList.begin(), addressRegList.end(), [] (int lh, int rh) { return lh < rh; });

    QModbusDataUnit::RegisterType type = QModbusDataUnit::HoldingRegisters;
    int newStartAddress = addressRegList.at(0);
    int size = addressRegList.last() - addressRegList.first();

    QModbusDataUnit modbusDataUnit(type,
                                   newStartAddress,
                                   size);

    //--------------------------------------------
    ModbusRequest *modbusRequest = new ModbusRequest(modbusConnectionSettings,
                                                     addr,
                                                     1000,
                                                     this);

    connect(modbusRequest, &ModbusRequest::wantExecuteQuery,
            this, &ModbusMasterUnit::executeQuery);
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterUnit::executeQuery(ModbusRequest *request)
{
    SEND_TO_LOG( QString("%1 - Постановка запроса в очередь на выполнение [%2]")
                 .arg(objectName()).arg(request->objectName()) );

    m_handler->reconnect(request->connectionSettings());

}
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

