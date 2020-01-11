#include "MsgWidget.h"

//------------------------------------------------------------------------------------
//!
MsgWidget::MsgWidget(ScriptObject *scriptObject,
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
MsgWidget::~MsgWidget()
{

}
//------------------------------------------------------------------------------------
//!
void MsgWidget::paintEvent(QPaintEvent *paintEvent)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    QWidget::paintEvent(paintEvent);
}
//------------------------------------------------------------------------------------
//!
