#ifndef MODBUSMASTERUNITTESTFORM_H
#define MODBUSMASTERUNITTESTFORM_H
//------------------------------------------------------------------------------------
#include <QWidget>

//------------------------------------------------------------------------------------
#ifdef __arm__
//------------------------------------------------------------------------------------
    #ifndef NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
// Include these libraries for using the RS-485 and Modbus functions
#include "arduPi.h"
#include "ModbusMaster485.h"
//------------------------------------------------------------------------------------
    #endif // !NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
#endif // __arm__
//------------------------------------------------------------------------------------

#include "Log.h"
#include "DbUnit.h"
#include "ScriptUnit.h"
#include "ModbusMasterUnit.h"
//------------------------------------------------------------------------------------
//!
namespace Ui {
class ModbusMasterUnitTestForm;
}
//------------------------------------------------------------------------------------
//!
class ModbusMasterUnitTestForm : public QWidget
{
        Q_OBJECT

    public:
        explicit ModbusMasterUnitTestForm(QWidget *parent = nullptr);
        virtual ~ModbusMasterUnitTestForm();

//------------------------------------------------------------------------------------
#ifdef __arm__
//------------------------------------------------------------------------------------
    #ifndef NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
        void setup(const int baudRate,
                   const uint8_t &slaveAddress,
                   const int &functionCode,
                   QList<std::tuple<int, QString, QString> > &registerList);
//------------------------------------------------------------------------------------
    #endif // !NATIVE_MODBUS_HANDLER
//------------------------------------------------------------------------------------
#endif // __arm__
//------------------------------------------------------------------------------------


    private:
        Ui::ModbusMasterUnitTestForm *ui;

        DbUnit             m_dbUnit;
        ScriptUnit         m_scriptUnit;
        ModbusMasterUnit   m_modbusMasterUnit;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNITTESTFORM_H
