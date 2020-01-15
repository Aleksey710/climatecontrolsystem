#ifndef MODBUSMASTERUNITTESTFORM_H
#define MODBUSMASTERUNITTESTFORM_H
//------------------------------------------------------------------------------------
#include <QWidget>


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

    private:
        Ui::ModbusMasterUnitTestForm *ui;

        std::shared_ptr<DbUnit>             m_dbUnit;
        std::shared_ptr<ScriptUnit>         m_scriptUnit;
        std::shared_ptr<ModbusMasterUnit>   m_modbusMasterUnit;
};
//------------------------------------------------------------------------------------
#endif // MODBUSMASTERUNITTESTFORM_H
