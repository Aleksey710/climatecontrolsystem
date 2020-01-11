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
    setStyleSheet(
        "QWidget{ "
        "padding: 10px;"
        "margin: 10px;"
//        "border: 1px solid #000000;"
//        "border-radius : 5px;"
//        "color: blue;"
//        "background-color: yellow;"
        "}"
    );

    QGridLayout *layout = new QGridLayout();

    setLayout(layout);
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
        m_isError = false;
    }

    m_curentData = value;
    update();
}
//------------------------------------------------------------------------------------
//!
void DigitalStripIndicator::paintEvent(QPaintEvent *)
{
    //qDebug() << "DigitalStripIndicator::paintEvent";

    QStyleOption opt;
    opt.init(this);

    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    painter.setRenderHint(QPainter::Antialiasing);
    //painter.translate(width(), height());
    //painter.scale(width(), height());

    QColor positiveColor(255, 0, 0);
    QColor negativeColor(0, 0, 255);
    QColor transparentColor(0, 255, 0, 20);

    qreal stripHeight = 5;

    qreal percent = (qreal)width()/abs(m_maximum - m_minimum);
    //--------------------------------------------
    //! Нарисовать контур
    painter.setPen(Qt::SolidLine);
    painter.setBrush(transparentColor);

    QRectF rectangle(0, 0, width(), stripHeight);
    painter.drawRect(rectangle);

    //--------------------------------------------
    qreal digWidth = 26;
    qreal indentHeight = 4;
    qreal digHeight = 12;

    //! значение минимума
    painter.drawText(QRect(0, stripHeight+indentHeight, digWidth, stripHeight+indentHeight+digHeight),
                     Qt::AlignCenter, QString("%1").arg(m_minimum));
    //---------------------
    //! значение максимума
    painter.drawText(QRect(width()-digWidth, stripHeight+indentHeight, digWidth, stripHeight+indentHeight+digHeight),
                     Qt::AlignCenter, QString("%1").arg(m_maximum));

    setMinimumHeight(stripHeight+indentHeight+digHeight+5);
    //--------------------------------------------
    if(m_curentData < 100)
        m_curentData = -m_curentData;

    //qDebug() << "DigitalStripIndicator::paintEvent контур percent" << rectangle << percent;
    //--------------------------------------------
    if( !m_isError )
    {
        //! Нарисовать данные
        if ( m_minimum >= 0 &&
             m_maximum >= 0 )
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(positiveColor);

            painter.drawRect(0, 0, m_curentData*percent, stripHeight);
            //painter.drawRect(0, 0, width(), stripHeight);

        } else if( m_minimum <= 0 &&
                   m_maximum <= 0 )
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(negativeColor);

            //painter.translate(width(), 0);

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

            painter.drawText(QRect(-4, stripHeight+6, 8, 12), Qt::AlignCenter, "0");
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
    else
    {
        // отображение ошибки
        qDebug() << "Отображение ошибки";
    }
}
//------------------------------------------------------------------------------------
//!
