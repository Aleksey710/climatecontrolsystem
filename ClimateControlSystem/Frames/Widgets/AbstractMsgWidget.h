#ifndef ABSTRACTMSGWIDGET_H
#define ABSTRACTMSGWIDGET_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include "QLobel.h"
#include <QLabel>

#include "ScriptUnit.h"
#include "ScriptObject.h"
//------------------------------------------------------------------------------------
//!
class AbstractMsgWidget : public QLobel
{
        Q_OBJECT
    public:
        explicit AbstractMsgWidget(const QString &msg,
                                   QWidget *parent = nullptr)
                :QLobel(msg, parent)
            {}

        virtual ~AbstractMsgWidget()
            {  }

    signals:
        void displayed(bool state);

    protected:


};
//------------------------------------------------------------------------------------
#endif // ABSTRACTMSGWIDGET_H
