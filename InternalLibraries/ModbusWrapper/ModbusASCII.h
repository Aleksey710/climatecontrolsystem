#ifndef MODBUSASCII_H
#define MODBUSASCII_H
//------------------------------------------------------------------------------------


#include "ModbusSerial.h"
#include "modbus-ascii.h"
//------------------------------------------------------------------------------------
//!
class ModbusASCII : public ModbusSerial
{
        Q_OBJECT

    public:
        explicit ModbusASCII(const ModbusConnectionAddress &modbusConnectionAddress,
                             QObject *parent = nullptr);
        virtual ~ModbusASCII();

    protected:
        virtual bool mb_create();

};
//------------------------------------------------------------------------------------
#endif // MODBUSASCII_H
