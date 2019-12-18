#ifndef MODBUSSERIAL_H
#define MODBUSSERIAL_H
//------------------------------------------------------------------------------------


#include "ModbusCore.h"
//------------------------------------------------------------------------------------
//!
class ModbusSerial : public ModbusCore
{
        Q_OBJECT

    public:
        explicit ModbusSerial(const ModbusConnectionAddress &modbusConnectionAddress,
                              QObject *parent = nullptr);
        virtual ~ModbusSerial();

    protected:
        virtual bool mb_create() = 0;

        /*
        MODBUS_RTU_RS485
        MODBUS_RTU_RS232
        */
        bool set_serial_mode(int mode = MODBUS_RTU_RS485);

    protected:

};
//------------------------------------------------------------------------------------
#endif // MODBUSSERIAL_H
