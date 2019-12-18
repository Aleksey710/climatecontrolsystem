#ifndef MODBUSCONSTS_H
#define MODBUSCONSTS_H
//------------------------------------------------------------------------------------
#include <modbus.h>


//------------------------------------------------------------------------------------
// #include "ModbusConsts.h"
//------------------------------------------------------------------------------------
enum MODBUS_FUNCTIONS
{
    NONE_FUNCTION               = 0,
    READ_COILS                  = MODBUS_FC_READ_COILS,
    READ_DISCRETE_INPUTS        = MODBUS_FC_READ_DISCRETE_INPUTS,
    READ_HOLDING_REGISTERS      = MODBUS_FC_READ_HOLDING_REGISTERS,
    READ_INPUT_REGISTERS        = MODBUS_FC_READ_INPUT_REGISTERS,
    WRITE_SINGLE_COIL           = MODBUS_FC_WRITE_SINGLE_COIL,
    WRITE_SINGLE_REGISTER       = MODBUS_FC_WRITE_SINGLE_REGISTER,
    READ_EXCEPTION_STATUS       = MODBUS_FC_READ_EXCEPTION_STATUS,
    WRITE_MULTIPLE_COILS        = MODBUS_FC_WRITE_MULTIPLE_COILS,
    WRITE_MULTIPLE_REGISTERS    = MODBUS_FC_WRITE_MULTIPLE_REGISTERS,
    REPORT_SLAVE_ID             = MODBUS_FC_REPORT_SLAVE_ID,
    MASK_WRITE_REGISTER         = MODBUS_FC_MASK_WRITE_REGISTER,
    WRITE_AND_READ_REGISTERS    = MODBUS_FC_WRITE_AND_READ_REGISTERS
};
//------------------------------------------------------------------------------------
#endif // MODBUSCONSTS_H
