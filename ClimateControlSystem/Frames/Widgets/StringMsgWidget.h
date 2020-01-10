#ifndef STRINGMSGWIDGET_H
#define STRINGMSGWIDGET_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include "ScriptObject.h"
//------------------------------------------------------------------------------------
//!
class StringMsgWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit StringMsgWidget(ScriptObject *scriptObject,
                                 QHash<int, QString> msgList,
                                 QWidget *parent = nullptr);
        virtual ~StringMsgWidget();


    signals:
        void displayMsg(const QString &msg);

    protected:
        virtual void paintEvent(QPaintEvent *paintEvent);

    protected:
        ScriptObject *m_scriptObject;

        QHash<int, QString> m_msgList;
};
//------------------------------------------------------------------------------------
#endif // STRINGMSGWIDGET_H
