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
#include "ClimateControlSystem.h"
//
#include "ButtonsWidget.h"
//
#include "MainFrame.h"
#include "InOutDisplayFrame.h"
#include "CarInformationFrame.h"
#include "ConfigEditFrame.h"
#include "MenuConfigEditForm.h"
#include "DbUnit.h"
//
#include "ElectricalEquipmentArchiveForm.h"
#include "ClimateDeviceAutoArchiveForm.h"
#include "ClimateDeviceManualArchiveForm.h"
#include "WorkTimeArchiveForm.h"

//#include "ElectricalEquipmentOperatingTimeArchiveForm.h"


//#include ""

//------------------------------------------------------------------------------------
#ifdef __arm__
    #define FULL_SCREEN
#endif
//------------------------------------------------------------------------------------
//!
class MainDisplayWidget : public QWidget
{
        Q_OBJECT
    public:
        explicit MainDisplayWidget(QWidget *parent = nullptr);
        virtual ~MainDisplayWidget();

    signals:

    private:
        void setupFrames();
        void setupMenu();

    private:
        std::shared_ptr<ClimateControlSystem> m_climateControlSystem;

        QVBoxLayout     *m_mainLayout;

        QVBoxLayout     *m_frameLayout;

        ButtonsWidget   *m_buttonsWidget;

        QList<QWidget*> m_framesList;
        int             m_curentFrameId;

        QWidget         *m_curentWidget;
};
//------------------------------------------------------------------------------------
#endif // MAINDISPLAYWIDGET_H
