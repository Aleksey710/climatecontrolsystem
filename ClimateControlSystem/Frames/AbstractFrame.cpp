#include "AbstractFrame.h"

//------------------------------------------------------------------------------------
//!
AbstractFrame::AbstractFrame(QWidget *parent)
              :QWidget(parent)
{
    setStyleSheet(//"font: 12px; "
                  //"font-weight: bold; "
                  "margin: 0px, 0px, 0px, 0px;"
                  "padding: 0px, 0px, 0px, 0px; "
                  //"border:  1px solid black; "
                  );
}
//------------------------------------------------------------------------------------
//!
AbstractFrame::~AbstractFrame()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
void AbstractFrame::setupDisplay(const QString &name, QLabel *label)
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
void AbstractFrame::setupDisplay(const QString &name, QLineEdit *lineEdit)
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
void AbstractFrame::setupDigDisplay(const QString &name, QLineEdit *lineEdit)
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){

            if( scriptObject->data() )
            {
                lineEdit->setText(QString("Увiмкнено"));
            } else
            {
                lineEdit->setText(QString("Вимкнено"));
            }
        });

        //! Начальная инициализация виджета
        scriptObject->dataChanged();
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractFrame::setupDisplay(const QString &name, GigitalIndicatorWidget *displayWidget)
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
void AbstractFrame::setupDateDisplay(const QString &yearName,
                                      const QString &monthName,
                                      const QString &dayName,
                                      QLabel *label)
{
    ScriptObject *yearScriptObject = ScriptUnit::getScriptObject(yearName);

    if(yearScriptObject)
    {
        connect(yearScriptObject, &ScriptObject::dataChanged, [=](){
            QStringList dateList = label->text().split("-");

            //qDebug() << "AbstractFrames::setupDateDisplay yearScriptObject" << dateList << yearScriptObject->data();
            if(dateList.size() == 3)
            {
                label->setText( QString("%1-%2-%3")
                                .arg(yearScriptObject->data())
                                .arg(dateList.at(1))
                                .arg(dateList.at(2)));
            }
        });

        //! Начальная инициализация виджета
        yearScriptObject->dataChanged();
    }

    //-----------------------------------------------
    ScriptObject *monthScriptObject = ScriptUnit::getScriptObject(monthName);

    if(monthScriptObject)
    {
        connect(monthScriptObject, &ScriptObject::dataChanged, [=](){
            QStringList dateList = label->text().split("-");

            if(dateList.size() == 3)
            {
                label->setText( QString("%1-%2-%3")
                                .arg(dateList[0])
                                .arg(monthScriptObject->data())
                                .arg(dateList[2]));
            }
        });

        //! Начальная инициализация виджета
        monthScriptObject->dataChanged();
    }

    //-----------------------------------------------
    ScriptObject *dayScriptObject = ScriptUnit::getScriptObject(dayName);

    if(dayScriptObject)
    {
        connect(dayScriptObject, &ScriptObject::dataChanged, [=](){
            QStringList dateList = label->text().split("-");

            if(dateList.size() == 3)
            {
                label->setText( QString("%1-%2-%3")
                                .arg(dateList[0])
                                .arg(dateList[1])
                                .arg(dayScriptObject->data()));
            }
        });

        //! Начальная инициализация виджета
        dayScriptObject->dataChanged();
    }
}
