#ifndef MODBUSSLAVE_H
#define MODBUSSLAVE_H
//------------------------------------------------------------------------------------
#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#include <sys/time.h>
#endif
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include <modbus.h>
//#include <>
//#include <>

//#include ""
//#include ""
//#include ""
//#include ""
#include "ModbusPartner.h"
//------------------------------------------------------------------------------------
/* The goal of this program is to check all major functions of
   libmodbus:
   - write_coil
   - read_bits
   - write_coils
   - write_register
   - read_registers
   - write_registers
   - read_registers

   All these functions are called with random values on a address
   range defined by the following defines.
*/
#define LOOP             1
#define SERVER_ID       0x50
#define ADDRESS_START   0x100A
#define ADDRESS_END     0x100F

/* At each loop, the program works in the range ADDRESS_START to
 * ADDRESS_END then ADDRESS_START + 1 to ADDRESS_END and so on.
 */
//------------------------------------------------------------------------------------
//!
class ModbusSlave : public ModbusPartner
{
        Q_OBJECT
    public:
        explicit ModbusSlave(const QString &coreType,
                             const ModbusConnectionAddress &modbusConnectionAddress,
                             QObject *parent = nullptr);

        virtual ~ModbusSlave();

        //void initData();
        void read();

    signals:


    public slots:


    private:
        virtual void postInit();


        void loop();
        void testMaster(modbus_t *ctx);

    private:
        int m_rc;
        modbus_mapping_t *m_mb_mapping;
        uint8_t *m_query;

};
//------------------------------------------------------------------------------------
#endif // MODBUSSLAVE_H
