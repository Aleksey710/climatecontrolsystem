#ifndef MODBUSCONNECTIONADDRESS_H
#define MODBUSCONNECTIONADDRESS_H
//------------------------------------------------------------------------------------
#include <QString>

#include "ModbusType.h"
#include "modbus-private.h"
//------------------------------------------------------------------------------------
// #include "ModbusConnectionAddress.h"
//------------------------------------------------------------------------------------
//!
class ModbusConnectionAddress
{
    public:
        ModbusConnectionAddress()
            :device (     "ttyUSB1" ),
             baud (       115200 ),
             parity (     'N' ),            // N for none, E for even, O for odd
             data_bit (   8 ),              // allowed values are 5, 6, 7 and 8
             stop_bit (   1 ),              // allowed values are 1 and 2
             ip (         "127.0.0.1" ),
             port (       502 ),
             slave_addr ( 0x01 /*MODBUS_TCP_SLAVE*/ )
            { type = RTU; }

        ModbusConnectionAddress(const ModbusConnectionAddress &address)
            :type (       address.type ),
             //device (     address.device ),
             baud (       address.baud ),
             parity (     address.parity ),
             data_bit (   address.data_bit ),
             stop_bit (   address.stop_bit ),
             //ip (         address.ip ),
             port (       address.port ),
             slave_addr ( address.slave_addr )
            {
                strcpy(device, address.device);
                strcpy(ip, address.ip);
            }

        ModbusConnectionAddress(ModbusType      _type,
                                const QString   &_device,
                                int             _baud,
                                char            _parity,
                                int             _data_bit,
                                int             _stop_bit,
                                int             _slave_addr = MODBUS_TCP_SLAVE)
            :type (       _type ),
             baud (       _baud ),
             parity (     _parity ),
             data_bit (   _data_bit ),
             stop_bit (   _stop_bit ),
             slave_addr ( _slave_addr )
            {
                strcpy(device, qPrintable(_device));
            }


        ModbusConnectionAddress(const QString &_ip,
                                int            _port)
            :port ( _port ),
             s ( -1),
             slave_addr ( MODBUS_TCP_SLAVE )
            {
                type = TCP;
                strcpy(ip, qPrintable(_ip));
            }

        QString infoString()
        {
            switch (type)
            {
                case RTU:
                case ISI:
                case ASCII:
                    return QString("ModbusConnectionAddress(%1 %2 %3 %4 %5 %6 slaveAddr[%7])")
                            .arg(modbusTypeToString(type)).arg(device)
                            .arg(baud).arg(data_bit).arg(parity).arg(stop_bit).arg(slave_addr);
                    break;
                case TCP:
                    return QString("ModbusConnectionAddress(%1 %2 %3)")
                            .arg(modbusTypeToString(type)).arg(ip).arg(port);
                    break;

                default:
                    break;
            }

            return QString("ModbusConnectionAddress(none)");
        }

    public:
        ModbusType  type;

        char        device[50];
        QString     _device;
        int         baud;
        char        parity;
        int         data_bit;
        int         stop_bit;

        char        ip[50];
        int         port;
        int         s;

        int         slave_addr;
};
//------------------------------------------------------------------------------------
#endif // MODBUSCONNECTIONADDRESS_H
