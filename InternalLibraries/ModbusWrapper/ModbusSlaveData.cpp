#include "ModbusSlaveData.h"

//------------------------------------------------------------------------------------
//!
ModbusSlaveData::ModbusSlaveData(const uint16_t bits_start,
                                 const uint16_t bits_nb,
                                 const uint16_t input_bits_start,
                                 const uint16_t input_bits_nb,
                                 const uint16_t registers_start,
                                 const uint16_t registers_nb,
                                 const uint16_t input_registers_start,
                                 const uint16_t input_registers_nb)
{
    m_mb_mapping.nb_bits               = bits_nb;
    m_mb_mapping.start_bits            = bits_start;
    m_mb_mapping.nb_input_bits         = input_bits_nb;
    m_mb_mapping.start_input_bits      = input_bits_start;
    m_mb_mapping.nb_input_registers    = registers_nb;
    m_mb_mapping.start_input_registers = registers_start;
    m_mb_mapping.nb_registers          = input_registers_nb;
    m_mb_mapping.start_registers       = input_registers_start;


    m_bits              .resize(bits_nb);
    m_input_bits        .resize(input_bits_nb);
    m_input_registers   .resize(input_registers_nb);
    m_registers         .resize(registers_nb);

    m_mb_mapping.tab_bits              = m_bits.data();
    m_mb_mapping.tab_input_bits        = m_input_bits.data();
    m_mb_mapping.tab_registers         = m_registers.data();
    m_mb_mapping.tab_input_registers   = m_input_registers.data();
}
//------------------------------------------------------------------------------------
//!
ModbusSlaveData::~ModbusSlaveData()
{
    m_bits.clear();
    m_input_bits.clear();
    m_input_registers.clear();
    m_registers.clear();

    //qDebug() << "ModbusSlaveData::~ModbusSlaveData()";
}
//------------------------------------------------------------------------------------
//!
bool ModbusSlaveData::setBit(int address, uint8_t data)
{
    int mapping_address = address - m_mb_mapping.start_bits;

    if(mapping_address < 0 || mapping_address >= m_mb_mapping.nb_bits)
    {
        SEND_TO_LOG( QString("ModbusSlaveData::setBit %1 over range").arg( address ) );
        return false;
    }

    QMutexLocker mutexLocker(&m_bitsMutex);

    m_bits[mapping_address] = data;
    //m_bits.replace(mapping_address, data);

    return true;
}
//------------------------------------------------------------------------------------
//!
bool ModbusSlaveData::setInputBit(int address, uint8_t data)
{
    int mapping_address = address - m_mb_mapping.start_input_bits;

    if(mapping_address < 0 || mapping_address >= m_mb_mapping.nb_input_bits)
    {
        SEND_TO_LOG( QString("ModbusSlaveData::setInputBit %1 over range").arg( address ) );
        return false;
    }

    QMutexLocker mutexLocker(&m_inputBitsMutex);

    m_input_bits[mapping_address] = data;
    //m_bits.replace(mapping_address, data);

    return true;
}
//------------------------------------------------------------------------------------
//!
bool ModbusSlaveData::setRegister(int address, uint16_t data)
{
    int mapping_address = address - m_mb_mapping.start_registers;
    if(mapping_address < 0 || mapping_address >= m_mb_mapping.nb_registers)
    {
        SEND_TO_LOG( QString("ModbusSlaveData::setRegister %1 over range").arg( address ) );
        return false;
    }

    QMutexLocker mutexLocker(&m_registersMutex);


    m_registers[mapping_address] = data;
    //m_bits.replace(mapping_address, data);

    return true;
}
//------------------------------------------------------------------------------------
//!
bool ModbusSlaveData::setInputRegister(int address, uint16_t data)
{
    int mapping_address = address - m_mb_mapping.start_input_registers;

    if(mapping_address < 0 || mapping_address >= m_mb_mapping.nb_input_registers)
    {
        SEND_TO_LOG( QString("ModbusSlaveData::setRegister %1 over range").arg( address ) );
        return false;
    }

    QMutexLocker mutexLocker(&m_inputRegistersMutex);

    m_input_registers[mapping_address] = data;
    //m_bits.replace(mapping_address, data);

    return true;
}
//------------------------------------------------------------------------------------
//!
