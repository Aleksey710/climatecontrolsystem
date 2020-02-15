#ifndef MODBUSDATAUNIT_H
#define MODBUSDATAUNIT_H
//------------------------------------------------------------------------------------
#include <QVector>

//------------------------------------------------------------------------------------
//#include "ModbusDataUnit.h"
//------------------------------------------------------------------------------------
//!
class ModbusDataUnit
{
    public:
        ModbusDataUnit()
        {}

        ModbusDataUnit(const int __startAddress,
                       const int size)
            : startAddress ( __startAddress )
        {
            values.fill(0,size);
        }

        ModbusDataUnit(const int __startAddress,
                       const QVector<uint16_t> &__values)
            : startAddress ( __startAddress ),
              values ( __values )
        { }

        inline void setValue(int addr, uint16_t value )
        {
            values[addr - startAddress] = value;
        }

        inline void setValues(const QVector<uint16_t> &__values)
        {
            values = __values;
        }

        inline uint16_t value(const int addr) const
        {
            return values.at(addr-startAddress);
        }

        int                startAddress;
        QVector<uint16_t>  values;
};
//------------------------------------------------------------------------------------
#endif // MODBUSDATAUNIT_H
