#include "MainDisplayWidget.h"

//------------------------------------------------------------------------------------
//!
MainDisplayWidget::MainDisplayWidget(DbUnit *dbUnit,
                                     QWidget *parent)
                  : QWidget(parent),
                    m_dbUnit ( dbUnit )
{
    SEND_TO_LOG("Запуск MainDisplayWidget ");

    setStyleSheet(//"font: 12px; "
                  //"font-weight: bold; "
                  "margin: 0px, 0px, 0px, 0px;"
                  "padding: 0px, 0px, 0px, 0px; "
                  //"border:  1px solid black; "
                  );

    //! Задать имя окна
    //setWindowTitle(m_nameStation);

    //-----------------------------------------
    //! Создать главный слой - разделение меню и отображения
    m_mainLayout = new QVBoxLayout();

    m_mainLayout->setMargin(0);

    //! Поместить главный слой на главный виджет
    setLayout(m_mainLayout);

#ifdef Q_OS_LINUX
#ifdef FULL_SCREEN
    setWindowState(Qt::WindowFullScreen);
#endif
#endif
//    setWindowFlags( Qt::CustomizeWindowHint
//                   | Qt::FramelessWindowHint
//                   //| Qt::X11BypassWindowManagerHint
//                   | Qt::WindowStaysOnTopHint
//                   //| Qt::WA_DeleteOnClose
//                     );


//    Qt::FramelessWindowHint
//    Создает безрамочное окно.
//    Пользователь не может перемещать окно и изменять его размеры
//    с помощью оконное системы. В X11 результат действия флага зависит от
//    оконного менеджера и его способности понимать предпочтения Motif и/или NETWM.
//    С ними умеют обращаться наиболее современные из существующих оконных менеджеров.

//    Qt::WindowStaysOnTopHint
//    Сообщает оконной системе, что данной окно должно находиться выше всех других окон.
//    Обратите внимание, что на некоторых оконных менеджерах в X11, для правильной работы
//    с данным флагом, Вы также должны передать Qt::X11BypassWindowManagerHint.

//    Qt::X11BypassWindowManagerHint
//    Действует в обход оконного менеджера.
//    В результате получается совершенно неуправляемое окно без рамки
//    (т.е. не может получить фокус ввода клавиатуры, пока Вы не вызовите вручную QWidget::activateWindow()).

    //activateWindow();

//    int width  = qApp->desktop()->screenGeometry(0).width();
//    int height = qApp->desktop()->screenGeometry(0).height() / 2;

//    setSizePolicy(QSizePolicy::Fixed,
//                  QSizePolicy::Fixed);

    //-----------------------------------------------------------
    setupFrames();

    setupMenu();
    //-----------------------------------------------------------
#ifndef FULL_SCREEN
    setGeometry(0,0,800,480);
    setSizePolicy(QSizePolicy::Fixed,
                  QSizePolicy::Fixed);
#endif
    SEND_TO_LOG("MainDisplayWidget - создан");
    show();
}
//------------------------------------------------------------------------------------
//!
MainDisplayWidget::~MainDisplayWidget()
{
    SEND_TO_LOG("MainDisplayWidget - удален");
}
//------------------------------------------------------------------------------------
//!
void MainDisplayWidget::setupFrames()
{
    //! Создать главный слой - разделение меню и отображения
    m_frameLayout = new QVBoxLayout();

    m_frameLayout->setMargin(0);

    //! Добавить виджет на главный слой
    m_mainLayout->addLayout(m_frameLayout);

    //-----------------------------------------------------------
    MainFrame *mainFrame = new MainFrame();
    m_framesList.append(mainFrame);

    //-----------------------------------------------------------
    InOutDisplayFrame *inOutDisplayFrame = new InOutDisplayFrame();
    m_framesList.append(inOutDisplayFrame);

    //-----------------------------------------------------------
    CarInformationFrame *carInformationFrame = new CarInformationFrame();
    m_framesList.append(carInformationFrame);

    //-----------------------------------------------------------
    ClimateDeviceArchiveForm *climateDeviceArchiveForm
            = new ClimateDeviceArchiveForm();
    m_framesList.append(climateDeviceArchiveForm);

    //-----------------------------------------------------------
    ElectricalEquipmentArchiveForm *electricalEquipmentArchiveForm
        = new ElectricalEquipmentArchiveForm();
    m_framesList.append(electricalEquipmentArchiveForm);

    //-----------------------------------------------------------
    ElectricalEquipmentOperatingTimeArchiveForm *electricalEquipmentOperatingTimeArchiveForm
        = new ElectricalEquipmentOperatingTimeArchiveForm();
    m_framesList.append(electricalEquipmentOperatingTimeArchiveForm);

    //-----------------------------------------------------------
    // В случае, если объект уже удален, то p будет пустым указателем
    if( m_dbUnit )
    {
        m_framesList.append( new MenuConfigEditForm( m_dbUnit->settingsMenuItemList() ) );
    } else
    {
        SEND_TO_LOG("MainDisplayWidget - Error(Не инициализирован DbUnit)");
    }

    //-------------------------------------------------------------------
    m_curentFrameId = 0;
    m_frameLayout->addWidget(m_framesList[m_curentFrameId]);
}
//------------------------------------------------------------------------------------
//!
void MainDisplayWidget::setupMenu()
{
    m_buttonsWidget = new ButtonsWidget();
    m_mainLayout->addWidget(m_buttonsWidget);

    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::mainFrameClicked, [=](){
        if(m_curentFrameId == 0)
            return;

        m_framesList[m_curentFrameId]->setHidden(true);
        m_frameLayout->removeWidget( m_framesList[m_curentFrameId] );

        m_curentFrameId = 0;

        m_frameLayout->addWidget( m_framesList[m_curentFrameId] );
        m_framesList[m_curentFrameId]->setHidden(false);
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::nextFrameClicked, [=](){
        m_framesList[m_curentFrameId]->setHidden(true);
        m_frameLayout->removeWidget( m_framesList[m_curentFrameId] );

        if(m_curentFrameId == (m_framesList.size()-1))
        {
            m_curentFrameId = 0;
        } else
        {
            m_curentFrameId = m_curentFrameId + 1;
        }

        m_frameLayout->addWidget( m_framesList[m_curentFrameId] );
        m_framesList[m_curentFrameId]->setHidden(false);
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::previousFrameClicked, [=](){
        m_framesList[m_curentFrameId]->setHidden(true);
        m_frameLayout->removeWidget( m_framesList[m_curentFrameId] );

        if(m_curentFrameId == 0)
        {
            m_curentFrameId = m_framesList.size() - 1;
        } else
        {
            m_curentFrameId = m_curentFrameId - 1;
        }

        m_frameLayout->addWidget( m_framesList[m_curentFrameId] );
        m_framesList[m_curentFrameId]->setHidden(false);

    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::pgUpClicked, [=](){

    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::pgDownClicked, [=](){

    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::plusClicked, [=](){

    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::minusClicked, [=](){

    });
}













