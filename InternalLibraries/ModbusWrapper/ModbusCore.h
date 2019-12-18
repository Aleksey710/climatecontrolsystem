#ifndef MODBUSCORE_H
#define MODBUSCORE_H
//------------------------------------------------------------------------------------
#include "modbus.h"
#include <QVector>
#include <QObject>
//#include <>


//#include ""
//#include ""
//#include ""
//#include ""
#include "Log.h"
#include "ModbusConsts.h"
#include "ModbusConnectionAddress.h"
//------------------------------------------------------------------------------------
//!
class ModbusCore : public QObject
{
        Q_OBJECT

//    public:
//        enum ModbusCoreType {
//            ModbusRTU   = 1,
//            ModbusASCII = 2,
//            ModbusISI   = 3,
//            ModbusTCP   = 4
//        };

    protected:
        static const int DEFAULT_VALUE = 0;

    public:
        explicit ModbusCore(const ModbusConnectionAddress &modbusConnectionAddress,
                            QObject *parent = nullptr);
        virtual ~ModbusCore();

        inline modbus_t* modbus()
            { return m_ctx; }

        inline void setResponseTimeoutUsec(uint32_t timeout)
            { m_responseTimeout_ms = timeout; }

        inline void setSlaveAddress(int address = MODBUS_TCP_SLAVE)
            { m_slaveAddress = address; }

        inline bool init()
            {
                if( !mb_create() )
                {
                    return false;
                }

                if( !mb_connect() )
                {
                    return false;
                }

                return true;
            }


    protected:
        virtual bool mb_create() = 0;

        bool mb_connect();
        void mb_disconnnect();

        void commonInit();

    protected:
        modbus_t *m_ctx;

        modbus_backend_type_t m_modbus_backend_type_t;

        ModbusConnectionAddress m_modbusConnectionAddress;

        int m_slaveAddress;
        uint32_t m_responseTimeout_ms;
};
//------------------------------------------------------------------------------------
#endif // MODBUSCORE_H
