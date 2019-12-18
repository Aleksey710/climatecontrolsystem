#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H
//------------------------------------------------------------------------------------
#include <vector>

#include <QVector>
#include <QString>
#include <QObject>
#include <QMutex>
#include <QMutexLocker>
//#include <>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "modbus.h"
#include "modbus-serial.h"
#include "ModbusRequest.h"
#include "ModbusPartner.h"
//------------------------------------------------------------------------------------
//!
class ModbusMaster : public ModbusPartner
{
        Q_OBJECT
    public:
        explicit ModbusMaster(const QString &coreType,
                              const ModbusConnectionAddress &modbusConnectionAddress,
                              QObject *parent = nullptr);
        virtual ~ModbusMaster();

        ModbusData executeRequest(const ModbusRequest &modbusRequest);

        ModbusData read(int addr,
                        int nb,
                        MODBUS_FUNCTIONS funk,
                        int slaveAddress = MODBUS_TCP_SLAVE,
                        uint32_t responseTimeout_ms = 50);

        void write(int addr,
                   int nb,
                   MODBUS_FUNCTIONS funk,
                   int slaveAddress = MODBUS_TCP_SLAVE,
                   uint32_t responseTimeout_ms = 50);

/*
        The Modbus protocol defines different data types and functions to read and write them from/to remote devices. The following functions are used by the clients to send Modbus requests:

        Read data
        modbus_read_bits(3) modbus_read_input_bits(3) modbus_read_registers(3) modbus_read_input_registers(3) modbus_report_slave_id(3)

        Write data
        modbus_write_bit(3) modbus_write_register(3) modbus_write_bits(3) modbus_write_registers(3)

        Write and read data
        modbus_write_and_read_registers(3)

        Raw requests
        modbus_send_raw_request(3) modbus_receive_confirmation(3)

        Reply an exception
        modbus_reply_exception(3)
        */
    signals:


    public slots:


    protected:
        //! Счетчик попыток подключиться к порту
        int m_notFoundSerialDeviceErrorCount;

    private:



    private:
        QMutex m_mutex;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTER_H
