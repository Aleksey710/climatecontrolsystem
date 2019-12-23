#include "MainDisplayWidget.h"
//------------------------------------------------------------------------------------
//!
MainDisplayWidget::MainDisplayWidget(DataModel *dataModel,
                                     QWidget *parent)
                  : QWidget(parent),
                    m_dataModel ( dataModel )
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
    setWindowState(Qt::WindowFullScreen);
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
    //! Создать главный слой - разделение меню и отображения
    m_frameLayout = new QVBoxLayout();

    m_frameLayout->setMargin(0);

    //! Добавить виджет на главный слой
    m_mainLayout->addLayout(m_frameLayout);

    QString str("ИНИЦИАЛИЗАЦИЯ");

    m_curentWidget = new QLabel(QString("<font size=\"30\" color=\"red\" face=\"Arial\">%1</font>").arg(str));

    //m_frameLayout->addWidget(m_curentWidget);

    show();
}
//------------------------------------------------------------------------------------
//!
MainDisplayWidget::~MainDisplayWidget()
{

}
//------------------------------------------------------------------------------------
//!
