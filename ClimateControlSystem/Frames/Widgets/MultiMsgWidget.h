#ifndef MULTIMSGWIDGET_H
#define MULTIMSGWIDGET_H
//------------------------------------------------------------------------------------
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>

#include "ScriptUnit.h"
#include "ScriptObject.h"
#include "AbstractMsgWidget.h"
//------------------------------------------------------------------------------------
//!
class MultiMsgWidget : public AbstractMsgWidget
{
        Q_OBJECT
    public:
        MultiMsgWidget(QWidget *parent = nullptr);

        virtual ~MultiMsgWidget();

    private:
        void scriptObjectSetup(const QString &scriptObjectName);

        void display();


    private:
        QMap<QString, bool> m_regStateMap;
};
//------------------------------------------------------------------------------------
#endif // MULTIMSGWIDGET_H
