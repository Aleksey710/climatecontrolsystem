#include "GigitalIndicatorWidget.h"

#include "ScriptObject.h"
#include "ScriptUnit.h"
//------------------------------------------------------------------------------------
//!
GigitalIndicatorWidget::GigitalIndicatorWidget(const QString &title,
                                               const QString &measureTitle,
                                               const int minimum,
                                               const int maximum,
                                               const bool onlyT,
                                               QWidget *parent)
                       :QWidget(parent),
                        m_mainLayout ( new QGridLayout() ),
                        m_dataLabel ( new QLabel(measureTitle) ),
                        m_measureTitle ( measureTitle ),
                        m_digitalStripIndicator ( new DigitalStripIndicator(minimum, maximum) ),
                        m_onlyT ( onlyT ),
                        m_obrivSensorValue ( 1000 )
{
    setObjectName("GigitalIndicatorWidget");

    //----------------------------------------------
    ScriptObject *scriptObject = ScriptUnit::getScriptObject("settings.temp.sev");

    if(scriptObject)
    {
        m_obrivSensorValue = static_cast<int>( scriptObject->data() );
    }

    //----------------------------------------------
    m_mainLayout->setMargin(1);
    m_mainLayout->setVerticalSpacing(1);
    m_mainLayout->setHorizontalSpacing(1);

    QString baseStyleSheet = styleSheet();

    QGridLayout *rootLayout = new QGridLayout();
    rootLayout->setMargin(1);
    rootLayout->setVerticalSpacing(1);
    rootLayout->setHorizontalSpacing(1);

    QWidget *rootWidget = new QWidget();
    rootWidget->setObjectName("rootWidget");
    rootWidget->setStyleSheet(
        "QWidget#rootWidget {"
//        "padding: 0px;"
//        "margin: 5px;"
        "border: 1px solid #000000;"
        "border-radius : 5px;"
//        "color: blue;"
//        "background-color: yellow;"
        "}"
    );
    rootWidget->setLayout(rootLayout);
    //---------------------------------------------------------
    QFont titleFont = font();
    titleFont.setPointSize(titleFont.pointSize() + 3);
    titleFont.setBold(true);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    titleLabel->setFont(titleFont);
    rootLayout->addWidget(titleLabel);

    //---------------------------------------------------------
    QFont dataFont = font();
    dataFont.setPointSize(dataFont.pointSize() + 10);
    dataFont.setBold(true);

    m_dataLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_dataLabel->setFont(dataFont);
    rootLayout->addWidget(m_dataLabel);

    //---------------------------------------------------------
    rootLayout->addWidget(m_digitalStripIndicator);
    //---------------------------------------------------------
    m_mainLayout->addWidget(rootWidget);

    //---------------------------------------------------------
    //! Задать виджету слой
    setLayout(m_mainLayout);

    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
GigitalIndicatorWidget::~GigitalIndicatorWidget()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
double GigitalIndicatorWidget::data()
{
    QString curentText = m_dataLabel->text();
    return curentText.remove(m_measureTitle).toDouble();
}
//------------------------------------------------------------------------------------
//!
void GigitalIndicatorWidget::setData(const double &value)
{
    if(value >= m_obrivSensorValue &&
       m_onlyT)
    {
        m_digitalStripIndicator->setData(0);
        m_dataLabel->setText(QString("Обрив датчика"));
    } else
    {
        m_digitalStripIndicator->setData(value);
        m_dataLabel->setText(QString("%1 %2").arg(value).arg(m_measureTitle));
    }
}
//------------------------------------------------------------------------------------
//!
