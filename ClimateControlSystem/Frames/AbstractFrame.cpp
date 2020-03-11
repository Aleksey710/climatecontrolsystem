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
void AbstractFrame::setupStringDisplay(const QString &name, QLabel *label)
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){

            label->setText(QString("%1").arg(scriptObject->stringData()));
        });
        //! Начальная инициализация виджета
        scriptObject->dataChanged();
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractFrame::setupDisplay(const QString &name, QLabel *label)
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){
            double value = scriptObject->data();
            //if(value == std::numeric_limits<quint16>::max())
            if(value == 65535)
            {
                label->setText(QString("Обрив датчика"));
            } else
            {
                label->setText(QString("%1").arg( round(value*10)/10 ));
            }
        });
        //! Начальная инициализация виджета
        scriptObject->dataChanged();
    }
}
//------------------------------------------------------------------------------------
//!
void AbstractFrame::setupDisplay(const QString &name,
                                 QLineEdit *lineEdit,
                                 const QString &averageSizeScriptObjectName)
{
    if( !averageSizeScriptObjectName.isEmpty() )
    {
        DataAverager *dataAverager = new DataAverager(name,
                                                      averageSizeScriptObjectName,
                                                      lineEdit);

        connect(dataAverager, &DataAverager::dataUpdate, [=](const double value){
            //if(value == std::numeric_limits<quint16>::max())
            if(value == 65535)
            {
                lineEdit->setText(QString("Обрив датчика"));
            } else
            {
                lineEdit->setText(QString("%1").arg( round(value*10)/10 ));
            }
        });
    } else
    {
        ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

        if(scriptObject)
        {
            connect(scriptObject, &ScriptObject::dataChanged, [=](){
                double value = scriptObject->data();
                //if(value == std::numeric_limits<quint16>::max())
                if(value == 65535)
                {
                    lineEdit->setText(QString("Обрив датчика"));
                } else
                {
                    lineEdit->setText(QString("%1").arg( round(value*10)/10 ));
                }
            });

            //! Начальная инициализация виджета
            scriptObject->dataChanged();
        }
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
GigitalIndicatorWidget* AbstractFrame::createGigitalIndicatorWidget(const QString &name,
                                                                    const QString &title,
                                                                    const QString &measureTitle,
                                                                    const QString &minimumRegData,
                                                                    const QString &maximumRegData,
                                                                    const QString &averageSizeScriptObjectName)
{
    int minimum = 0;

    ScriptObject *minScriptObject = ScriptUnit::getScriptObject(minimumRegData);

    if(minScriptObject)
    {
        minimum = minScriptObject->data();
    }

    //--------------------------------------
    int maximum = 0;

    ScriptObject *maxScriptObject = ScriptUnit::getScriptObject(maximumRegData);

    if(maxScriptObject)
    {
        maximum = maxScriptObject->data();
    }

    //--------------------------------------
    return createGigitalIndicatorWidget(name,
                                        title,
                                        measureTitle,
                                        minimum,
                                        maximum,
                                        averageSizeScriptObjectName);
}
//------------------------------------------------------------------------------------
//!
GigitalIndicatorWidget* AbstractFrame::createGigitalIndicatorWidget(const QString &name,
                                                                    const QString &title,
                                                                    const QString &measureTitle,
                                                                    const int minimum,
                                                                    const int maximum,
                                                                    const QString &averageSizeScriptObjectName)
{
    GigitalIndicatorWidget *displayWidget = new GigitalIndicatorWidget(title,
                                                                       measureTitle,
                                                                       minimum,
                                                                       maximum);

    if( !averageSizeScriptObjectName.isEmpty() )
    {
        DataAverager *dataAverager = new DataAverager(name,
                                                      averageSizeScriptObjectName,
                                                      displayWidget);

        connect(dataAverager, &DataAverager::dataUpdate, [=](const double value){
            displayWidget->setData( round(value) );
        });
    } else
    {
        ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

        if(scriptObject)
        {
            connect(scriptObject, &ScriptObject::dataChanged, [=](){
                displayWidget->setData( round(scriptObject->data()) );
            });

            //! Начальная инициализация виджета
            scriptObject->dataChanged();
        }
    }

    return displayWidget;
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
