#include "AbstractFrames.h"

//------------------------------------------------------------------------------------
//!
AbstractFrames::AbstractFrames(QWidget *parent)
               : QWidget(parent)
{

}
//------------------------------------------------------------------------------------
//!
AbstractFrames::~AbstractFrames()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void AbstractFrames::setupDisplay(const QString &name, QLabel *label)
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){
            label->setText(QString("%1").arg(scriptObject->data()));
        });
        //! Начальная инициализация виджета
        scriptObject->dataChanged();
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractFrames::setupDisplay(const QString &name, QLineEdit *lineEdit)
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){
            lineEdit->setText(QString("%1").arg(scriptObject->data()));
        });

        //! Начальная инициализация виджета
        scriptObject->dataChanged();
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractFrames::setupDisplay(const QString &name, AbstractDisplayWidget *displayWidget)
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){
            displayWidget->setData(scriptObject->data());
        });

        //! Начальная инициализация виджета
        scriptObject->dataChanged();
    }
}
//------------------------------------------------------------------------------------
//!
