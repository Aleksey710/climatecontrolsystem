#ifndef MODBUSREQUEST_H
#define MODBUSREQUEST_H
//------------------------------------------------------------------------------------
#include "ModbusConsts.h"
//------------------------------------------------------------------------------------
// #include "ModbusRequest.h"
//------------------------------------------------------------------------------------
//!
class ModbusRequest
{
    public:
        ModbusRequest()
            :address ( 0 ),
             number ( 0 ),
             funk ( NONE_FUNCTION ),
             slaveAddress ( MODBUS_TCP_SLAVE ),
             responseTimeout_ms ( 100 )
        { }

        ModbusRequest(int _address,
                      int _number,
                      MODBUS_FUNCTIONS _funk,
                      int _slaveAddress = MODBUS_TCP_SLAVE,
                      uint32_t _responseTimeout_ms = 100)
            :address ( _address ),
             number ( _number ),
             funk ( _funk ),
             slaveAddress ( _slaveAddress ),
             responseTimeout_ms ( _responseTimeout_ms )
        { }

        int address;
        int number;
        MODBUS_FUNCTIONS funk;
        int slaveAddress;

        uint32_t responseTimeout_ms;
};
//------------------------------------------------------------------------------------
#endif // MODBUSREQUEST_H
