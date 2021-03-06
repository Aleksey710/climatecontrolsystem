#include "MainDisplayWidget.h"

#include <QMessageBox>

#ifdef FULL_SCREEN
 //   #undef FULL_SCREEN
#endif

//------------------------------------------------------------------------------------
//!
MainDisplayWidget::MainDisplayWidget(QWidget *parent)
                  : QWidget(parent),
                    m_menuConfigEditFrame ( nullptr )
{
    SEND_TO_LOG("Запуск MainDisplayWidget ");

    //m_climateControlSystem = new ClimateControlSystem(this);

    setStyleSheet(//"font: 12px; "
                  //"font-weight: bold; "
                  "margin: 3px, 5px, 3px, 3px;"
                  "padding: 0px, 0px, 0px, 0px; "
                  //"border:  1px solid black; "
                  );

    //! Задать имя окна
    //setWindowTitle(m_nameStation);

    //-----------------------------------------
    //! Создать главный слой - разделение меню и отображения
    m_mainLayout = new QVBoxLayout(this);

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
    QShortcut *shortcutEditSettings = new QShortcut(QKeySequence("Ctrl+E"), this);
    QObject::connect(shortcutEditSettings, &QShortcut::activated,
                     this, &MainDisplayWidget::startEditSettings);

    //-----------------------------------------------------------
    QShortcut *shortcutSetScreenBrightness = new QShortcut(QKeySequence("Ctrl+L"), this);
    QObject::connect(shortcutSetScreenBrightness, &QShortcut::activated,
                     this, &MainDisplayWidget::startEditScreenBrightness);

    QShortcut *shortcutUnmount = new QShortcut(QKeySequence("Ctrl+U"), this);
    QObject::connect(shortcutUnmount, &QShortcut::activated,
                     this, &MainDisplayWidget::umountFlash);

    //-----------------------------------------------------------
    SEND_TO_LOG("MainDisplayWidget - создан");

    //-----------------------------------------------------------
    QCursor::setPos(800,480);

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
    CarInformationFrame *carInformationFrame = new CarInformationFrame();
    m_framesList.append(carInformationFrame);

    //-----------------------------------------------------------
//    ElectricalEquipmentOperatingTimeArchiveFrame *electricalEquipmentOperatingTimeArchiveFrame
//        = new ElectricalEquipmentOperatingTimeArchiveFrame();
//    m_framesList.append(electricalEquipmentOperatingTimeArchiveFrame);

    //-----------------------------------------------------------
    //-----------------------------------------------------------
    //if( m_climateControlSystem->dbUnit().get() )
    if( m_climateControlSystem.dbUnit() )
    {
        //m_menuItemDataList=m_climateControlSystem->dbUnit().get()->settingsMenuItemList();
        m_menuItemDataList=m_climateControlSystem.dbUnit()->settingsMenuItemList();
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

    connect(this, &MainDisplayWidget::frameChanged,
            m_buttonsWidget, &ButtonsWidget::setFrameName);
    m_mainLayout->addWidget(m_buttonsWidget);

    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::mainFrameClicked, [=](){

        if(m_curentFrameId == 0)
            return;

        //! Скрыть
        m_framesList[m_curentFrameId]->setHidden(true);        
        m_frameLayout->removeWidget( m_framesList[m_curentFrameId] );

        m_curentFrameId = 0;

        m_frameLayout->addWidget( m_framesList[m_curentFrameId] );
        //! Отобразить
        m_framesList[m_curentFrameId]->setHidden(false);
        //! Испустить сигнал, о том , что виджет стал отображаться
        m_framesList[m_curentFrameId]->showed();

        emit frameChanged(m_framesList[m_curentFrameId]->frameName());
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::nextFrameClicked, [=](){
        //! Скрыть
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
        //! Отобразить
        m_framesList[m_curentFrameId]->setHidden(false);
        //! Испустить сигнал, о том , что виджет стал отображаться
        m_framesList[m_curentFrameId]->showed();

        emit frameChanged(m_framesList[m_curentFrameId]->frameName());
    });
    //-------------------------------------------------------------------
    connect(m_buttonsWidget, &ButtonsWidget::previousFrameClicked, [=](){
        //! Скрыть
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
        //! Отобразить
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
    if(m_menuConfigEditFrame)
        return;

    CheckPasswordWidget *checkPasswordWidget =
        new CheckPasswordWidget([=](){
            m_menuConfigEditFrame = new MenuConfigEditFrame(m_menuItemDataList);
            m_menuConfigEditFrame->setAttribute(Qt::WA_DeleteOnClose);

            //! Скрыть
            m_framesList[m_curentFrameId]->setHidden(true);

            m_frameLayout->removeWidget(m_framesList[m_curentFrameId]);
            m_frameLayout->addWidget( m_menuConfigEditFrame );

            emit frameChanged(FrameName::MenuConfigEdit);

            //----------------------------------------------------
            connect(m_menuConfigEditFrame, &QWidget::destroyed,[=](){

                m_frameLayout->removeWidget( m_menuConfigEditFrame );
                m_frameLayout->addWidget( m_framesList[m_curentFrameId] );
                m_menuConfigEditFrame = nullptr;

                m_framesList[m_curentFrameId]->setHidden(false);

                emit frameChanged(m_framesList[m_curentFrameId]->frameName());
            });
        });

    Q_UNUSED(checkPasswordWidget);
}
//------------------------------------------------------------------------------------
//!
void MainDisplayWidget::startEditScreenBrightness()
{
    if(m_menuConfigEditFrame)
        return;

    CheckPasswordWidget *checkPasswordWidget =
        new CheckPasswordWidget([=](){
            SetScreenBrightnessForm *setScreenBrightnessForm = new SetScreenBrightnessForm();

            setScreenBrightnessForm->show();

            //----------------------------------------------------
            connect(setScreenBrightnessForm, &QWidget::destroyed,[=](){

            });
        });

    Q_UNUSED(checkPasswordWidget);
}

void MainDisplayWidget::umountFlash()
{

    QDir mediaDir("/media/pi");
    {
        QList<QString> flashDirList = mediaDir.entryList(QDir::Dirs);

        flashDirList.removeAll(".");
        flashDirList.removeAll("..");

        foreach(QString folder, flashDirList)
        {
            QString cmd = QString("sudo umount /media/pi/%1").arg(folder);
            int result = 0;
#ifdef __arm__
            result = QProcess::execute( cmd );
#endif
            qDebug() << "MainDisplayWidget::umountFlash" << cmd << result;
        }
    }
    {
        QList<QString> flashDirList = mediaDir.entryList(QDir::Dirs);

        flashDirList.removeAll(".");
        flashDirList.removeAll("..");

        QString msg;
        QMessageBox::Icon icon;
        if ( flashDirList.isEmpty() )
        {
            msg = QString("Флеш диск можна видалити");
            icon = QMessageBox::Information;
        } else {
            msg = QString("Не вiдмонтованi наступнi диски:\n");
            foreach(QString folder, flashDirList)
            {
                msg += folder + QString("\n");
            }
            icon = QMessageBox::Warning;
        }

        QMessageBox * msgBox = new QMessageBox(
                    icon,
                    "Вiдмонтуваня диску",
                    msg);

        QFont f = msgBox->font();
        f.setPointSize(12);
        msgBox->setFont( f );

        msgBox->show();

        //! Удалить транспарант о сохранении
        QTimer::singleShot(3*1000, [msgBox](){
            msgBox->deleteLater();
        });
    }
}
//------------------------------------------------------------------------------------










