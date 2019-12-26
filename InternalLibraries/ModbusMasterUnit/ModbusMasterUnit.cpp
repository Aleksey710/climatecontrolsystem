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
QStringList ModbusMasterUnit::initQueryModbusUnitStringList()
{
    QStringList queryStringList;

    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `modbus_types` ( "
                           "`id` TINYINT UNSIGNED NOT NULL DEFAULT 0, PRIMARY KEY (id), "
                           "`type` VARCHAR(6) NOT NULL"
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8;"
                           ));
    queryStringList.append(QStringLiteral("INSERT INTO `modbus_types` (`id`,`type`) VALUES (0,'RTU');"));
    queryStringList.append(QStringLiteral("INSERT INTO `modbus_types` (`id`,`type`) VALUES (1,'TCP');"));
    queryStringList.append(QStringLiteral("INSERT INTO `modbus_types` (`id`,`type`) VALUES (2,'ASCII');"));
    queryStringList.append(QStringLiteral("INSERT INTO `modbus_types` (`id`,`type`) VALUES (3,'ISI');"));

    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `baud_rate_types` ( "
                           "`id` TINYINT UNSIGNED NOT NULL DEFAULT 0, PRIMARY KEY (id), "
                           "`type` MEDIUMINT UNSIGNED NOT NULL"
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8;"
                           ));
    queryStringList.append(QStringLiteral("INSERT INTO `baud_rate_types` (`id`,`type`) VALUES (0,9600);"));
    queryStringList.append(QStringLiteral("INSERT INTO `baud_rate_types` (`id`,`type`) VALUES (1,19200);"));
    queryStringList.append(QStringLiteral("INSERT INTO `baud_rate_types` (`id`,`type`) VALUES (2,38400);"));
    queryStringList.append(QStringLiteral("INSERT INTO `baud_rate_types` (`id`,`type`) VALUES (3,57600);"));
    queryStringList.append(QStringLiteral("INSERT INTO `baud_rate_types` (`id`,`type`) VALUES (4,115200);"));
    queryStringList.append(QStringLiteral("INSERT INTO `baud_rate_types` (`id`,`type`) VALUES (5,921600);"));

    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `parity_types` ( "
                           "`id` TINYINT UNSIGNED NOT NULL DEFAULT 0, PRIMARY KEY (id), "
                           "`type` CHAR(1) NOT NULL,"
                           "`title` VARCHAR(45) NOT NULL "
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8;"
                           ));
    queryStringList.append(QStringLiteral("INSERT INTO `parity_types` (`id`,`type`,`title`) "
                                          "VALUES (0,'N','No parity');"));
    queryStringList.append(QStringLiteral("INSERT INTO `parity_types` (`id`,`type`,`title`) "
                                          "VALUES (1,'E','Even parity');"));
    queryStringList.append(QStringLiteral("INSERT INTO `parity_types` (`id`,`type`,`title`) "
                                          "VALUES (2,'O','Odd parity');"));
    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `data_bits_types` ( "
                           "`id` TINYINT UNSIGNED NOT NULL DEFAULT 0, PRIMARY KEY (id), "
                           "`type` TINYINT UNSIGNED NOT NULL"
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8;"
                           ));
    queryStringList.append(QStringLiteral("INSERT INTO `data_bits_types` (`id`,`type`) VALUES (0,7);"));
    queryStringList.append(QStringLiteral("INSERT INTO `data_bits_types` (`id`,`type`) VALUES (1,8);"));
    queryStringList.append(QStringLiteral("INSERT INTO `data_bits_types` (`id`,`type`) VALUES (2,9);"));
    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `stop_bits_types` ( "
                           "`id` TINYINT UNSIGNED NOT NULL DEFAULT 0, PRIMARY KEY (id), "
                           "`type` DECIMAL(2,1) NOT NULL"
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8;"
                           ));
    queryStringList.append(QStringLiteral("INSERT INTO `stop_bits_types` (`id`,`type`) VALUES (0,1);"));
    queryStringList.append(QStringLiteral("INSERT INTO `stop_bits_types` (`id`,`type`) VALUES (1,1.5);"));
    queryStringList.append(QStringLiteral("INSERT INTO `stop_bits_types` (`id`,`type`) VALUES (2,2);"));

    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `modbus_connections` ( "
                           "`id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (`id`), "
                           "`title` NVARCHAR(45) NOT NULL, "
                           "`dpd_type_id` TINYINT UNSIGNED NOT NULL DEFAULT 0, "
                           "FOREIGN KEY (dpd_type_id) REFERENCES dpd_types(id) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           "`uart_port_name` VARCHAR(45) NOT NULL DEFAULT 'none', "
                           "`topic_name` VARCHAR(45) NOT NULL, "
                           "`baud_rate_type_id` TINYINT UNSIGNED NOT NULL DEFAULT 4, "
                           "FOREIGN KEY (baud_rate_type_id) REFERENCES baud_rate_types(id) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           "`parity_type_id` TINYINT UNSIGNED NOT NULL DEFAULT 0, "
                           "FOREIGN KEY (parity_type_id) REFERENCES parity_types(id) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           "`data_bits_type_id` TINYINT UNSIGNED NOT NULL DEFAULT 0, "
                           "FOREIGN KEY (data_bits_type_id) REFERENCES data_bits_types(id) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           "`stop_bits_type_id` TINYINT UNSIGNED NOT NULL DEFAULT 0, "
                           "FOREIGN KEY (stop_bits_type_id) REFERENCES stop_bits_types(id) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           "`modbus_type_id` TINYINT UNSIGNED NOT NULL, "
                           "FOREIGN KEY (`modbus_type_id`) REFERENCES modbus_types(`id`) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           //-----------------
                           "`ip_address` VARCHAR(50) NOT NULL DEFAULT '127.0.0.1', "
                           "`tcp_port` SMALLINT UNSIGNED NOT NULL DEFAULT 0 "
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8; "
                           ));

    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `modbus_devices` ( "
                           "`id` SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (`id`), "
                           "`device_id` MEDIUMINT UNSIGNED NOT NULL DEFAULT 0, "
                           "FOREIGN KEY (`device_id`) REFERENCES devices(`id`) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           //"`title` VARCHAR(100) NOT NULL, "
                           "`topic_name` VARCHAR(45) NOT NULL, "
                           "`slave_address` TINYINT UNSIGNED NOT NULL, "
                           "`modbus_connection_id` SMALLINT UNSIGNED NOT NULL, "
                           "FOREIGN KEY (`modbus_connection_id`) REFERENCES modbus_connections(`id`) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           //----------------------------
                           "`uuid` VARCHAR(36) NOT NULL DEFAULT '00000000-0000-0000-0000-000000000000', "
                           "`pos_data_model_x` DOUBLE NOT NULL DEFAULT 0, "
                           "`pos_data_model_y` DOUBLE NOT NULL DEFAULT 0 "
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8;"
                           ));
    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `modbus_functions` ( "
                           "`id` TINYINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (id), "
                           "`function` TINYINT UNSIGNED NOT NULL, "
                           "UNIQUE(`function`),"
                           "`title` VARCHAR(30) NOT NULL "
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8; "
                           ));

    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (1,1,'Read coils');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (2,2,'Read discrete inputs');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (3,3,'Read holding registers');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (4,4,'Read input registers');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (5,5,'Write single coil');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (6,6,'Write single register');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (7,7,'Read exception status');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (8,15,'Write multiple coils');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (9,16,'Write multiple registers');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (10,17,'Report slave id');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (11,22,'Mask write register');"));
    queryStringList.append(QString("INSERT INTO `modbus_functions` (`id`,`function`,`title`) "
                                   "VALUES (12,23,'Write and read registers');"));

    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `modbus_requesters` ( "
                           "`id` MEDIUMINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (`id`), "
                           "`period_ms` SMALLINT UNSIGNED NOT NULL, "
                           "`timeout_ms` SMALLINT UNSIGNED NOT NULL, "
                           "`function_id` TINYINT UNSIGNED NOT NULL, "
                           "`start_address` SMALLINT UNSIGNED NOT NULL, "
                           "FOREIGN KEY (`function_id`) REFERENCES modbus_functions(`id`) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           "`modbus_device_id` SMALLINT UNSIGNED NOT NULL, "
                           "FOREIGN KEY (`modbus_device_id`) REFERENCES modbus_devices(`id`) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION "
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8; "
                           ));
    //----------------------------------------------------------------
    queryStringList.append(QStringLiteral(
                           "CREATE TABLE IF NOT EXISTS `modbus_registers` ( "
                           "`id` MEDIUMINT UNSIGNED NOT NULL AUTO_INCREMENT, PRIMARY KEY (`id`), "
                           "`number` SMALLINT UNSIGNED NOT NULL, "
                           "`title` NVARCHAR(200) NOT NULL, "
                           "`topic_name` VARCHAR(45) NOT NULL, "
                           "`is_used` TINYINT(1) NOT NULL, "
                           //
                           "`modbus_data_source_type_id` TINYINT UNSIGNED NOT NULL DEFAULT 1, "
                           "FOREIGN KEY (`modbus_data_source_type_id`) REFERENCES modbus_data_source_types(`id`) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION, "
                           "`lower_range_limit` SMALLINT UNSIGNED NOT NULL DEFAULT 1, "
                           "`curent_value` SMALLINT UNSIGNED NOT NULL DEFAULT 100, "
                           "`upper_range_limit` SMALLINT UNSIGNED NOT NULL DEFAULT 300, "
                           //
                           "`chanel_number` TINYINT UNSIGNED NOT NULL, "
                           "`connection_point_name` VARCHAR(10) NOT NULL, "
                           //
                           "`modbus_requester_id` MEDIUMINT UNSIGNED NOT NULL, "
                           "FOREIGN KEY (`modbus_requester_id`) REFERENCES modbus_requesters(`id`) "
                           "ON UPDATE CASCADE "
                           "ON DELETE NO ACTION "
                           ") "
                           //"#ROW_FORMAT=DYNAMIC "
                           "ROW_FORMAT=COMPRESSED "
                           //"#KEY_BLOCK_SIZE=8 "
                           "ENGINE = InnoDB CHARACTER SET=UTF8;"
                           ));

    //----------------------------------------------------------------
    return queryStringList;

}
