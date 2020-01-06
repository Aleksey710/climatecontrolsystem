#include "DigitalStripIndicator.h"

//------------------------------------------------------------------------------------
//!
DigitalStripIndicator::DigitalStripIndicator(const int minimum,
                                             const int maximum,
                                             QWidget *parent)
                      :QWidget(parent),
                       m_minimum ( minimum ),
                       m_maximum ( maximum ),
                       m_curentData ( 0 ),
                       m_isError ( false )

{
//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//    timer->start(1000);

    setStyleSheet(
        "QWidget{ "
        "padding: 1px;"
        "margin: 1px;"
        "border: 1px solid black;"
        "border-radius : 3px;"
        "}"
    );
}
//------------------------------------------------------------------------------------
//!
DigitalStripIndicator::~DigitalStripIndicator()
{

}
//------------------------------------------------------------------------------------
//!
void DigitalStripIndicator::setData(const double &value)
{
    if(value < m_minimum ||
       value > m_maximum )
    {
        m_isError = true;
    } else
    {
        m_isError = true;
    }

    m_curentData = value;
    update();
}
//------------------------------------------------------------------------------------
//!
void DigitalStripIndicator::paintEvent(QPaintEvent *)
{
    qDebug() << "DigitalStripIndicator::paintEvent";

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.translate(width(), height());
    //painter.scale(width(), height());

    QColor positiveColor(255, 0, 0);
    QColor negativeColor(0, 0, 255);
    QColor transparentColor(0, 255, 0, 20);

    qreal stripHeight = 5;

    qreal percent = width()/abs(m_maximum - m_minimum);
    //--------------------------------------------
    //! Нарисовать контур
    painter.setPen(Qt::SolidLine);
    painter.setBrush(transparentColor);

    QRectF rectangle(0, 0, width(), stripHeight);
    painter.drawRect(rectangle);
    //--------------------------------------------
    //if( !m_isError )
    {
        //! Нарисовать данные
        if ( m_minimum >= 0 &&
             m_maximum >= 0 )
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(positiveColor);

            painter.drawRect(0, 0, m_curentData*percent, stripHeight);

        } else if( m_minimum <= 0 &&
                   m_maximum <= 0 )
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(negativeColor);

            painter.translate(width(), 0);

            painter.drawRect(0, 0, m_curentData*percent, stripHeight);
        } else if( m_minimum < 0 &&
                   m_maximum > 0 )
        {
            //-----------------------------------------------
            qreal zerro = abs(percent*m_minimum);

            painter.translate(zerro, 0);

            painter.setPen(Qt::SolidLine);
            painter.setBrush(QColor(255,255,255));
            painter.drawRect(-1, 0, 2, stripHeight+4);

            //-----------------------------------------------
            painter.setPen(Qt::NoPen);
            if(m_curentData > 0)
            {
                painter.setBrush(positiveColor);
            } else if(m_curentData < 0)
            {
                painter.setBrush(negativeColor);
            } else {
                painter.setBrush(transparentColor);
            }
            //-----------------------------------------------
            painter.drawRect(0, 0, m_curentData*percent, stripHeight);
        }
    }
//    else
//    {
//        // отображение ошибки
//    }
}
//------------------------------------------------------------------------------------
//!
