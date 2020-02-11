#ifndef MSGWIDGET_H
#define MSGWIDGET_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>

#include "ScriptUnit.h"
#include "ScriptObject.h"
//------------------------------------------------------------------------------------
//!
class MsgWidget : public QLabel
{
        Q_OBJECT
    public:
        explicit MsgWidget(const QString &scriptObjectName,
                           const QString &msg,
                           const QString &color,
                           const QString &backgroundColor = "",
                           QWidget *parent = nullptr)
                :QLabel(msg, parent)
            {
                setStyleSheet(QString(
                    "QLabel{ "
                    //"padding: 1px;"
                    //"margin: 1px;"
                    //"border: 1px solid #000000;"
                    //"border: 2px solid #005500;"
                    "border: 2px solid %1;"
                    "border-radius : 5px;"
                    "color: %1;"
                    "%2"
                    "}")
                   //.arg("#005500")
                   .arg(color)
                   .arg( (backgroundColor.isEmpty()) ? QString() : QString("background-color: %1;").arg(backgroundColor) )
                );

                QFont titleFont = font();
                titleFont.setPointSize(titleFont.pointSize() + 3);

                setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                setFont(titleFont);

                ScriptObject *scriptObject = ScriptUnit::getScriptObject(scriptObjectName);

                if(scriptObject)
                {
                    connect(scriptObject, &ScriptObject::dataChanged, [=](){

                        if( scriptObject->data() == 1 )
                        {
                            setVisible(true);
                            emit displayed(true);
                        } else
                        {
                            setVisible(false);
                            emit displayed(false);
                        }
                    });

                    //! Начальная инициализация виджета
                    scriptObject->dataChanged();
                }
            }

        virtual ~MsgWidget()
            {  }

    signals:
        void displayed(bool state);

    protected:

};
//------------------------------------------------------------------------------------
#endif // MSGWIDGET_H
