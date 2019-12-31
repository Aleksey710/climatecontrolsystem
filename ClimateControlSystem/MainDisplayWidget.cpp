#include "MainDisplayWidget.h"
//------------------------------------------------------------------------------------
//!
MainDisplayWidget::MainDisplayWidget(const std::shared_ptr<DataModel> &dataModel,
                                     const std::shared_ptr<DbUnit> &dbUnit,
                                     QWidget *parent)
                  : QWidget(parent),
                    m_dataModel ( dataModel ),
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
    //setWindowState(Qt::WindowFullScreen);
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
    //! Создание заголовка
    //createHeader();
    //-----------------------------------------------------------
    QString str("ИНИЦИАЛИЗАЦИЯ");

    m_curentWidget = new QLabel(QString("<font size=\"30\" color=\"red\" face=\"Arial\">%1</font>").arg(str));

    //-----------------------------------------------------------
    setupFrames();

    setupMenu();

    //m_frameLayout->addWidget(m_curentWidget);

    //-----------------------------------------------------------
    setGeometry(0,0,800,480);
    setSizePolicy(QSizePolicy::Fixed,
                  QSizePolicy::Fixed);
    show();
}
//------------------------------------------------------------------------------------
//!
MainDisplayWidget::~MainDisplayWidget()
{

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
    // В случае, если объект уже удален, то p будет пустым указателем
    if( std::shared_ptr<DbUnit> p = m_dbUnit.lock() )
    {
        //std::shared_ptr<MenuConfigEditForm> menuConfigEditForm
        //        = std::make_shared<MenuConfigEditForm>(p->menuItemDataList());

        m_framesList.append( new MenuConfigEditForm( p->menuItemDataList() ) );
    }

    //-------------------------------------------------------------------
    m_curentFrameId = 0;
    m_frameLayout->addWidget(m_framesList[0]);
}
//------------------------------------------------------------------------------------
//!
void MainDisplayWidget::setupMenu()
{
    QFont buttonFont = font();
    buttonFont.setPointSize(buttonFont.pointSize() + 10);

    int buttonHeight = 60;
    //-------------------------------------------------------------------
    m_menuLayout = new QHBoxLayout();

    //-------------------------------------------------------------------
    QPushButton *mainFrameButton = new QPushButton("На главную");

    mainFrameButton->setFixedHeight(buttonHeight);
    mainFrameButton->setFont(buttonFont);

    connect(mainFrameButton, &QPushButton::clicked,
            [=](){

        if(m_curentFrameId == 0)
            return;

        m_framesList[m_curentFrameId]->setHidden(true);
        m_frameLayout->removeWidget( m_framesList[m_curentFrameId] );

        m_curentFrameId = 0;

        m_frameLayout->addWidget( m_framesList[m_curentFrameId] );
        m_framesList[m_curentFrameId]->setHidden(false);
    });

    m_menuLayout->addWidget(mainFrameButton);
    //-------------------------------------------------------------------
    QPushButton *previousFrameButton = new QPushButton("Предыдущий экран");

    previousFrameButton->setFixedHeight(buttonHeight);
    previousFrameButton->setFont(buttonFont);

    connect(previousFrameButton, &QPushButton::clicked,
            [=](){

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

    m_menuLayout->addWidget(previousFrameButton);
    //-------------------------------------------------------------------
    QPushButton *nextFrameButton = new QPushButton("Следующий экран");

    nextFrameButton->setFixedHeight(buttonHeight);
    nextFrameButton->setFont(buttonFont);

    connect(nextFrameButton, &QPushButton::clicked,
            [=](){

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

    m_menuLayout->addWidget(nextFrameButton);
    //-------------------------------------------------------------------
    /*
    QPushButton *nextButton = new QPushButton("Следующий экран");

    mainFrameButton->setFixedHeight(50);

    connect(nextButton, &QPushButton::click,
            [=](){

    });
    m_menuLayout->addWidget(nextButton);
    */
    //-------------------------------------------------------------------
    m_mainLayout->addLayout(m_menuLayout);
}













