#include "ModbusMasterUnitTestForm.h"
#include "ui_ModbusMasterUnitTestForm.h"

//------------------------------------------------------------------------------------
//!
ModbusMasterUnitTestForm::ModbusMasterUnitTestForm(QWidget *parent)
                         :QWidget(parent),
                          ui(new Ui::ModbusMasterUnitTestForm)
{
    ui->setupUi(this);

    m_dbUnit              = std::make_shared<DbUnit>();
    m_scriptUnit          = std::make_shared<ScriptUnit>();
    m_modbusMasterUnit    = std::make_shared<ModbusMasterUnit>();
}
//------------------------------------------------------------------------------------
//!
ModbusMasterUnitTestForm::~ModbusMasterUnitTestForm()
{
    delete ui;

    if(m_modbusMasterUnit.get())
        m_modbusMasterUnit->deleteLater();

    if(m_scriptUnit.get())
        m_scriptUnit->deleteLater();

    if(m_dbUnit.get())
        m_dbUnit->deleteLater();
}
//------------------------------------------------------------------------------------
//!

