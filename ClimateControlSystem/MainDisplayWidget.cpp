#include "MainDisplayWidget.h"

//------------------------------------------------------------------------------------
//!
MainDisplayWidget::MainDisplayWidget(QWidget *parent)
                  : QWidget(parent)
{
    SEND_TO_LOG("Запуск MainDisplayWidget ");

    m_climateControlSystem = std::make_shared<ClimateControlSystem>();

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

    //-----------------------------------------------------------
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+E"), this);
    QObject::connect(shortcut, &QShortcut::activated,
                     this, &MainDisplayWidget::startEditSettings);

    //-----------------------------------------------------------
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
    m_mainFrame = new MainFrame();
    //! Должен быть первым(id=0) в списке
    m_framesList.append(m_mainFrame);

    //-----------------------------------------------------------
    InOutDisplayFrame *inOutDisplayFrame = new InOutDisplayFrame();
    m_framesList.append(inOutDisplayFrame);

    //-----------------------------------------------------------
    CarInformationFrame *carInformationFrame = new CarInformationFrame();
    m_framesList.append(carInformationFrame);

    //-----------------------------------------------------------
    // ARCHIVE FRAMES
    //-----------------------------------------------------------
    ElectricalEquipmentArchiveFrame *electricalEquipmentArchiveFrame
        = new ElectricalEquipmentArchiveFrame();
    m_framesList.append(electricalEquipmentArchiveFrame);

    ClimateDeviceAutoArchiveFrame *climateDeviceAutoArchiveFrame
            = new ClimateDeviceAutoArchiveFrame();
    m_framesList.append(climateDeviceAutoArchiveFrame);

    ClimateDeviceManualArchiveFrame *climateDeviceManualArchiveFrame
            = new ClimateDeviceManualArchiveFrame();
    m_framesList.append(climateDeviceManualArchiveFrame);

    WorkTimeArchiveFrame *workTimeArchiveFrame
        = new WorkTimeArchiveFrame();
    m_framesList.append(workTimeArchiveFrame);

    //-----------------------------------------------------------
//    ElectricalEquipmentOperatingTimeArchiveFrame *electricalEquipmentOperatingTimeArchiveFrame
//        = new ElectricalEquipmentOperatingTimeArchiveFrame();
//    m_framesList.append(electricalEquipmentOperatingTimeArchiveFrame);

    //-----------------------------------------------------------
    //-----------------------------------------------------------
    if( m_climateControlSystem->dbUnit().get() )
    {
        m_menuItemDataList=m_climateControlSystem->dbUnit().get()->settingsMenuItemList();
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
    connect(this, &MainDisplayWidget::frameChanged, m_buttonsWidget, &ButtonsWidget::setFrameName);

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

        emit frameChanged(m_framesList[m_curentFrameId]->frameName());
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

        emit frameChanged(m_framesList[m_curentFrameId]->frameName());
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

        emit frameChanged(m_framesList[m_curentFrameId]->frameName());
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::pgUpClicked, [=](){
        (static_cast<AbstractArchiveFrame*>(m_framesList[m_curentFrameId]))->pgUp();
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::pgDownClicked, [=](){
        (static_cast<AbstractArchiveFrame*>(m_framesList[m_curentFrameId]))->pgDown();
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::plusClicked, [=](){
        m_mainFrame->tUstPlus();
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::minusClicked, [=](){
        m_mainFrame->tUstMinus();
    });
}
//------------------------------------------------------------------------------------
//!
void MainDisplayWidget::startEditSettings()
{
    m_menuConfigEditFrame = new MenuConfigEditFrame(m_menuItemDataList);

    m_framesList[m_curentFrameId]->setHidden(true);
    m_frameLayout->addWidget( m_menuConfigEditFrame );

    emit frameChanged(FrameName::MenuConfigEdit);

    //----------------------------------------------------
    connect(m_menuConfigEditFrame, &QWidget::destroyed,[=](){
        m_menuConfigEditFrame = nullptr;        
        m_framesList[m_curentFrameId]->setHidden(false);

        emit frameChanged(m_framesList[m_curentFrameId]->frameName());
    });
}












