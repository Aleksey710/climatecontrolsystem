#ifndef MAINDISPLAYWIDGET_H
#define MAINDISPLAYWIDGET_H
//------------------------------------------------------------------------------------
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QString>
#include <QObject>
#include <QPushButton>
#include <QFont>
#include <QList>
//#include <>
//#include <>


#include "Log.h"
#include "ScriptUnit.h"
//
#include "MainFrame.h"
#include "InOutDisplayFrame.h"
#include "CarInformationFrame.h"
#include "ConfigEditFrame.h"
#include "MenuConfigEditForm.h"
#include "DbUnit.h"
//
#include "ClimateDeviceArchiveForm.h"
#include "ElectricalEquipmentArchiveForm.h"
#include "ElectricalEquipmentOperatingTimeArchiveForm.h"
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//#define FULL_SCREEN
//------------------------------------------------------------------------------------
//!
class MainDisplayWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit MainDisplayWidget(const std::shared_ptr<DbUnit> &dbUnit,
                                   QWidget *parent = nullptr);
        virtual ~MainDisplayWidget();

    signals:

    private:
        void setupFrames();
        void setupMenu();

    private:
        std::weak_ptr<DbUnit>       m_dbUnit;

        QVBoxLayout     *m_mainLayout;

        QVBoxLayout     *m_frameLayout;
        QHBoxLayout     *m_menuLayout;

        QList<QWidget*> m_framesList;
        int             m_curentFrameId;

        QWidget         *m_curentWidget;
};
//------------------------------------------------------------------------------------
#endif // MAINDISPLAYWIDGET_H
