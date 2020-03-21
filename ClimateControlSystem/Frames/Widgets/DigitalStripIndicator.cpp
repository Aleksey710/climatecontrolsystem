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
        "padding: 0px;"
        "margin: 0px;"
        //"border: 1px solid #000000;"
        //"border-radius : 2px;"
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

    qreal borderPercent = 0.03;
    painter.translate(painter.window().width()*borderPercent, 0);
    painter.scale(1-(2*borderPercent), 1);

//    QColor positiveColor(255, 0, 0);
//    QColor negativeColor(0, 0, 255);
    QColor positiveColor(0, 150, 0);
    QColor negativeColor(0, 150, 0);

    QColor transparentColor(0, 255, 0, 20);

    qreal stripHeight = 5;

    qreal percent = (qreal)(width())/abs(m_maximum - m_minimum);
    //--------------------------------------------
    //! Нарисовать контур
    painter.setPen(Qt::SolidLine);
    painter.setBrush(transparentColor);

    QRectF rectangle(0, 0, width(), stripHeight);
    painter.drawRect(rectangle);

    //--------------------------------------------
    qreal digWidth      = 30;   // ширина цифры
    qreal indentHeight  = 4;    // промежуток между линией и цифрой
    qreal digHeight     = 12;   // высота цифры

    //! подписать значение минимума
    painter.drawText(QRect(0, stripHeight+indentHeight, digWidth, stripHeight+indentHeight+digHeight),
                     Qt::AlignCenter, QString("%1").arg(m_minimum));

    //---------------------
    //! подписать значение максимума
    painter.drawText(QRect(width()-digWidth, stripHeight+indentHeight, digWidth, stripHeight+indentHeight+digHeight),
                     Qt::AlignCenter, QString("%1").arg(m_maximum));

    setMinimumWidth(digWidth*3);
    setMinimumHeight(stripHeight+indentHeight+digHeight+5);
    //--------------------------------------------
//    if(m_curentData < 100)
//        m_curentData = -m_curentData;

    //qDebug() << "DigitalStripIndicator::paintEvent контур percent" << rectangle << percent;
    //--------------------------------------------
    if(m_curentData > m_maximum)
        m_curentData = m_maximum;

    if(m_curentData < m_minimum)
        m_curentData = m_minimum;

    //---------------------
    if( !m_isError )
    {
        //! Нарисовать данные
        if ( m_minimum >= 0 &&
             m_maximum >= 0 )
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(positiveColor);

            painter.drawRect(0, 0, (m_curentData - m_minimum)*percent, stripHeight);
        } else if( m_minimum <= 0 &&
                   m_maximum <= 0 )
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(negativeColor);

            painter.drawRect(width(), 0, width()-(-(m_curentData))*percent, stripHeight);
        } else if( m_minimum < 0 &&
                   m_maximum > 0 )
        {
            //-----------------------------------------------
            qreal zerro = abs(percent*m_minimum);

            painter.translate(zerro, 0);

            painter.setPen(Qt::SolidLine);
            painter.setBrush(QColor(255,255,255));
            painter.drawRect(-1, 0, 2, stripHeight+4);

            painter.drawText(QRect(-4, stripHeight+indentHeight,
                                   8 /*digWidth*/, stripHeight+indentHeight+digHeight),
                             Qt::AlignCenter, "0");
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
        painter.drawText(QRect(0, 0, width(), stripHeight+indentHeight+digHeight),
                         Qt::AlignCenter,
                         //QString("Error[%1]").arg(m_curentData)
                         QString("Обрив датчика")
                         );

        //qDebug() << "Отображение ошибки" << m_minimum << m_curentData << m_maximum;
    }
}
//------------------------------------------------------------------------------------
//!
