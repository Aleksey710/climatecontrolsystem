#include "ModbusMasterUnit.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterUnit::ModbusMasterUnit(QObject *parent)
                 :QObject(parent)
{
    setObjectName("ModbusMasterUnit");
    //-------------------------------------------

    const QString serialPortNameParameter       = "/dev/ttyUSB0";
    const int serialParityParameter             = QSerialPort::Parity::NoParity;
    const int serialBaudRateParameter           = QSerialPort::BaudRate::Baud115200;
    const int serialDataBitsParameter           = QSerialPort::DataBits::Data8;
    const int serialStopBitsParameter           = QSerialPort::StopBits::OneStop;
    //
    const QString &networkAddressParameter      = "192.168.22.55";
    const int networkPortParameter              = 502;
    //
    const ModbusConnection modbusConnectionType = ModbusConnection::Serial;
    //
    const int responseTime                      = 50;
    const int numberOfRetries                   = 5;

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

    m_modbusMasterHandler->reconnect(modbusConnectionSettings);

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан (%2)").arg(objectName()).arg( (quint64)thread() ) );
}
//------------------------------------------------------------------------------------
//!
ModbusMasterUnit::~ModbusMasterUnit()
{

}
//------------------------------------------------------------------------------------
//!
