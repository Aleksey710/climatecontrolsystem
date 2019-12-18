#ifndef MODBUSRTU_H
#define MODBUSRTU_H
//------------------------------------------------------------------------------------


#include "ModbusSerial.h"
#include "modbus-rtu.h"
//------------------------------------------------------------------------------------
//!
class ModbusRTU : public ModbusSerial
{
        Q_OBJECT

    public:
        explicit ModbusRTU(const ModbusConnectionAddress &modbusConnectionAddress,
                           QObject *parent = nullptr);

        virtual ~ModbusRTU();

    protected:
        virtual bool mb_create();

};
//------------------------------------------------------------------------------------
#endif // MODBUSRTU_H
