#include "ModbusConnectionInterrogator.h"

//------------------------------------------------------------------------------------
//!
ModbusConnectionInterrogator::ModbusConnectionInterrogator(const ModbusConnectionSettings &modbusConnectionSettings,
                                                           QObject *parent)
                             :QObject(parent),
                              m_modbusConnectionSettings ( modbusConnectionSettings )
{

}
//------------------------------------------------------------------------------------
//!
ModbusConnectionInterrogator::~ModbusConnectionInterrogator()
{

}
//------------------------------------------------------------------------------------
//!
