#ifndef MODBUSSLAVEDATA_H
#define MODBUSSLAVEDATA_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>
#include <QMutex>



#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "Log.h"
#include "ModbusConnectionAddress.h"

#include "modbus.h"
//------------------------------------------------------------------------------------
//!
class ModbusSlaveData
{
    public:
        ModbusSlaveData(const uint16_t bits_start,
                        const uint16_t bits_nb,
                        const uint16_t input_bits_start,
                        const uint16_t input_bits_nb,
                        const uint16_t registers_start,
                        const uint16_t registers_nb,
                        const uint16_t input_registers_start,
                        const uint16_t input_registers_nb);

        ~ModbusSlaveData();

        inline modbus_mapping_t* modbusMapping()
        {
            return &m_mb_mapping;
        }


        bool setBit(int address, uint8_t data);
        bool setInputBit(int address, uint8_t data);
        bool setRegister(int address, uint16_t data);
        bool setInputRegister(int address, uint16_t data);

        inline QVector<uint8_t>* bits()
        {
            return &m_bits;
        }

        inline QVector<uint8_t>* input_bits()
        {
            return &m_input_bits;
        }

        inline QVector<uint16_t>* input_registers()
        {
            return &m_input_registers;
        }

        inline QVector<uint16_t>* registers()
        {
            return &m_registers;
        }

        void setEnabled(bool val)
        {
            m_enabled = val;
        }

        bool isEnabled()
        {
            return m_enabled;
        }

    private:
        modbus_mapping_t m_mb_mapping;

        QMutex m_bitsMutex;
        QMutex m_inputBitsMutex;
        QMutex m_registersMutex;
        QMutex m_inputRegistersMutex;

        QVector<uint8_t>  m_bits;
        QVector<uint8_t>  m_input_bits;
        QVector<uint16_t> m_input_registers;
        QVector<uint16_t> m_registers;

        bool m_enabled = true;
};
//------------------------------------------------------------------------------------
#endif // MODBUSSLAVEDATA_H
