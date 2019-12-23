#ifndef MAINDISPLAYWIDGET_H
#define MAINDISPLAYWIDGET_H
//------------------------------------------------------------------------------------
//#include <>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QObject>



#include "Log.h"
#include "DataModel.h"
#include "DataModelConfigurator.h"
//#include ""
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//!
class MainDisplayWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit MainDisplayWidget(DataModel *dataModel,
                                   QWidget *parent = nullptr);
        virtual ~MainDisplayWidget();

    signals:

    private:
        DataModel       m_dataModel;

        //QWidget         *m_mainWidget;

        QVBoxLayout     *m_mainLayout;

        QVBoxLayout     *m_frameLayout;

        QWidget         *m_curentWidget;
};
//------------------------------------------------------------------------------------
#endif // MAINDISPLAYWIDGET_H
