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
#include <QShortcut>
//#include <>
//#include <>


#include "Log.h"
#include "DbUnit.h"
#include "ScriptUnit.h"
#include "ClimateControlSystem.h"
//
#include "FrameName.h"
#include "ButtonsWidget.h"
//
#include "AbstractArchiveFrame.h"
#include "MainFrame.h"
#include "InOutDisplayFrame.h"
#include "CarInformationFrame.h"
#include "ConfigEditFrame.h"
#include "MenuConfigEditFrame.h"
//
#include "ElectricalEquipmentArchiveFrame.h"
#include "ClimateDeviceAutoArchiveFrame.h"
#include "ClimateDeviceManualArchiveFrame.h"
#include "WorkTimeArchiveFrame.h"
//
//#include "ElectricalEquipmentOperatingTimeArchiveFrame.h"
//
#include "ConfigEditFrame.h"
#include "MenuConfigEditFrame.h"
#include "NumericKeypadWidget.h"
//#include ""
//#include ""
//#include ""
//#include ""
//------------------------------------------------------------------------------------
//! При сборке на архитектуре ARM приложение при запуске развернется на весь экран
//! При сборке на других архитектурах - обычный оконный режим (удобно для отладки)
//! Размеры окна, 800х480, приближены к рабочим.
#ifdef __arm__
    #define FULL_SCREEN
#endif
//if(QSysInfo::currentCpuArchitecture() == "arm")
//------------------------------------------------------------------------------------
//!
class MainDisplayWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit MainDisplayWidget(QWidget *parent = nullptr);
        virtual ~MainDisplayWidget();

    signals:
        void frameChanged(const FrameName &frameName);

    public slots:



    private slots:
        void startEditSettings();

    private:
        void setupFrames();
        void setupMenu();

    private:
        ClimateControlSystem    m_climateControlSystem;

        QVBoxLayout             *m_mainLayout;
        QVBoxLayout             *m_frameLayout;

        ButtonsWidget           *m_buttonsWidget;

        MainFrame               *m_mainFrame;

        QList<MenuItemData>     m_menuItemDataList;
        MenuConfigEditFrame     *m_menuConfigEditFrame;


        QList<AbstractFrame*>   m_framesList;

        int                     m_curentFrameId;
        AbstractFrame           *m_curentFrame;
};
//------------------------------------------------------------------------------------
#endif // MAINDISPLAYWIDGET_H
