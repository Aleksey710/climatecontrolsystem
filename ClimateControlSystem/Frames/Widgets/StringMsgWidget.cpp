#include "StringMsgWidget.h"

//------------------------------------------------------------------------------------
//!
StringMsgWidget::StringMsgWidget(ScriptObject *scriptObject,
                                 QHash<int, QString> msgList,
                                 QWidget *parent)
                :QWidget(parent),
                 m_scriptObject ( scriptObject ),
                 m_msgList ( msgList )
{
    connect(scriptObject, &ScriptObject::dataChanged, [&](){

        QString msg = m_msgList.value(static_cast<int>( scriptObject->data() ), QString());

        if( !msg.isEmpty() )
        {
            emit displayMsg(msg);
        } else
        {
            //emit hideWidget();
        }

        update();
    });
}
//------------------------------------------------------------------------------------
//!
StringMsgWidget::~StringMsgWidget()
{

}
//------------------------------------------------------------------------------------
//!
void StringMsgWidget::paintEvent(QPaintEvent *paintEvent)
{

    QWidget::paintEvent(paintEvent);
}
//------------------------------------------------------------------------------------
//!
