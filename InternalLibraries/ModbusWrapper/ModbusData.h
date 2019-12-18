#ifndef MODBUSDATA_H
#define MODBUSDATA_H
//------------------------------------------------------------------------------------
#include <stdint.h>
#include <array>
#include <algorithm>
#include <initializer_list>

#include <QVector>
#include <QDebug>


#include "modbus.h"
//------------------------------------------------------------------------------------
// #include "ModbusData.h"
//------------------------------------------------------------------------------------
//!
class ModbusData
{
    public:
        inline ModbusData(int _addr = 0,
                          int _nb = 1,
                          int _stateError = -1)
            : address ( _addr ),
              number ( _nb ),
              stateError ( _stateError ),
              data ( QVector<uint16_t>(_nb, 0) )
        {
            /*qDebug() <<  "ModbusData" << _addr << _nb << data.size();*/
            //d.data.reserve( sizeof array/sizeof(T) );
        }

        ~ModbusData()
        { }

        inline uint16_t getData(int _addr, int *err = nullptr) const
        {
            if(stateError != 0)
                return 0;

            if(err != nullptr &&
               _addr >= data.size())
            {
                *err = -1;
            }

            return data.value(_addr - address, 0);
        }

//        inline void setData(int _addr, uint16_t _data, int *err = nullptr)
//        {
//            if(err != nullptr &&
//               _addr >= data.size())
//            {
//                *err = -1;
//            }

//            data[_addr - address] = _data;
//        }

        inline int size() const
        {
            return data.size();
        }

        template <typename T>
        static ModbusData fromArray(T *array, int _addr, int _nb, int _stateError=-1)
        {
            ModbusData d(_addr, _nb, _stateError);

            //std::copy(std::begin(&array), std::end(&array), std::back_inserter(d.data));

            for (int i = 0; i < _nb; ++i)
            {
                //qDebug() << "ModbusData fromArray" << i << array[i];
                d.data[i] = array[i];
            }

            return d;
        }

        inline QString stateErrorString() const
            { return QString(modbus_strerror(stateError)); }

        inline QString info() const
            {
                QString info;
                info.append(QString("[addr:%1 num:%2 err:%3(%4)]-[")
                            .arg(address).arg(number).arg(stateError).arg(stateErrorString()));

                for (int i = 0; i < data.size(); ++i)
                {
                    //info.append( QString("0x%1 ").arg(data.at(i) );
                    info.append( QString("0x%1 ").arg(data.at(i), 0, 16) );
                    //info.append( QString("0x%1 ").number(data.at(i), 16) );
                }

                info.append("]");

                return info;
            }

    public:
        int address;
        int number;

        //! 0 - норма
        //! остальное = ошибки
        int stateError;

    private:
        QVector<uint16_t> data;

};
//------------------------------------------------------------------------------------
#endif // MODBUSDATA_H
