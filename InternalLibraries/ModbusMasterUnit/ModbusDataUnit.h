#ifndef MODBUSDATAUNIT_H
#define MODBUSDATAUNIT_H
//------------------------------------------------------------------------------------
#include <QVector>

//------------------------------------------------------------------------------------
//#include "ModbusDataUnit.h"
//------------------------------------------------------------------------------------
//template < typename T = uint16_t >
class ModbusDataUnit
{
    public:
        ModbusDataUnit()
        {}

        ModbusDataUnit(const int __startAddress,
                       const int nb)
            : startAddress ( __startAddress )
        {
            values.fill(0, nb);

//            values = (T*) malloc(nb * sizeof(T));
//            memset(values, 0, nb * sizeof(T));
        }

        inline void setValue(int addr, const uint16_t value )
        {
            values[addr - startAddress] = value;
        }

        inline void setValues(const QVector<uint16_t> &__values)
        {
            values = __values;
        }

        inline uint16_t value(const int addr) const
        {
            return values[addr-startAddress];
        }
/*
        template < class T, size_t N>
        std::size_t length(const T (&)[N])
        {
            return N;
        };
*/
        int startAddress;
        QVector<uint16_t>  values;
        //T   *values;
};
//------------------------------------------------------------------------------------
#endif // MODBUSDATAUNIT_H
