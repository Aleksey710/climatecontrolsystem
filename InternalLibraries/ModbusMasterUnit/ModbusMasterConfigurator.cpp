#include "ModbusMasterConfigurator.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterConfigurator::ModbusMasterConfigurator(DataModel *dataModel,
                                                   QObject *parent)
                         :AbstractConfigurator("ModbusMasterConfigurator",
                                               parent),
                          m_dataModel ( dataModel )
{
    setup( loadFile( QString("./conf/modbus.conf") ) );

    //-------------------------------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterConfigurator::~ModbusMasterConfigurator()
{

}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::setup(const QJsonObject &confJsonObject)
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
void ModbusMasterConfigurator::connectionParsing(const QJsonObject &connectionJsonObject)
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
        deviceParsing(deviceJsonObject);
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::deviceParsing(const QJsonObject &deviceJsonObject)
{
    const int addr          = deviceJsonObject.value("addr").toInt();
    const QString title     = deviceJsonObject.value("title").toString();
    const int funktion      = static_cast<QModbusPdu::FunctionCode>(deviceJsonObject.value("funktion").toInt());

    QJsonArray registersJsonArray   = deviceJsonObject.value("registers").toArray();

    foreach (const QJsonValue &value, registersJsonArray)
    {
        const QJsonObject registerJsonObject = value.toObject();
        registerParsing(registerJsonObject);
    }
}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::registerParsing(const QJsonObject &registerJsonObject)
{
    const int id          = registerJsonObject.value("id").toInt();
    const QString title   = registerJsonObject.value("title").toString();


}
//------------------------------------------------------------------------------------
//!
void ModbusMasterConfigurator::startWorkInAThread(const ModbusConnectionSettings &modbusConnectionSettings)
{
    ModbusConnectionController *modbusConnectionController
            = new ModbusConnectionController(modbusConnectionSettings);
//    connect(modbusConnectionController, &ModbusConnectionController::resultReady,
//            this, &MyObject::handleResults);

    connect(modbusConnectionController, &ModbusConnectionController::finished,
            modbusConnectionController, &QObject::deleteLater);
    modbusConnectionController->start();
}

