#ifndef MODBUSTCP_H
#define MODBUSTCP_H
//------------------------------------------------------------------------------------


#include "ModbusCore.h"
#include "modbus-tcp.h"
//------------------------------------------------------------------------------------
//!
class ModbusTCP : public ModbusCore
{
        Q_OBJECT
    public:
        explicit ModbusTCP(const ModbusConnectionAddress &modbusConnectionAddress,
                           QObject *parent = nullptr);
        virtual ~ModbusTCP();

    protected:
        virtual bool mb_create();

};
//------------------------------------------------------------------------------------
#endif // MODBUSTCP_H
