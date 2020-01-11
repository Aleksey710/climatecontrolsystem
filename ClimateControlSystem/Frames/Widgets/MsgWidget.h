#ifndef MSGWIDGET_H
#define MSGWIDGET_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include "ScriptObject.h"
//------------------------------------------------------------------------------------
//!
class MsgWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit MsgWidget(ScriptObject *scriptObject,
                           QHash<int, QString> msgList,
                           QWidget *parent = nullptr);
        virtual ~MsgWidget();


    signals:
        void displayMsg(const QString &msg);

    protected:
        virtual void paintEvent(QPaintEvent *paintEvent);

    protected:
        ScriptObject *m_scriptObject;

        QHash<int, QString> m_msgList;
};
//------------------------------------------------------------------------------------
#endif // MSGWIDGET_H
