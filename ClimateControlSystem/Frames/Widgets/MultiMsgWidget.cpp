#include "MultiMsgWidget.h"

//------------------------------------------------------------------------------------
//!
MultiMsgWidget::MultiMsgWidget(QWidget *parent)
               :AbstractMsgWidget(QString(), parent)
{
    QString color               = "#FFFFFF";
    QString backgroundColor     = "#FF0000";

    setStyleSheet(QString(
        "QLabel{ "
        "padding: 0px;"
        "margin: 0px;"
        "border: 2px solid %1;"
        "border-radius : 5px;"
        "color: %1;"
        "%2"
        "}")
       .arg(color)
       .arg( (backgroundColor.isEmpty()) ?
                 QString() :
                 QString("background-color: %1;").arg(backgroundColor) )
    );

    QFont titleFont = font();
    titleFont.setPointSize(titleFont.pointSize() + 2);
    titleFont.setBold(true);

    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setFont(titleFont);

    //--------------------------------------------------------------------
    //    vr.msg.automodeDisabledVvo - Не можливий авто. режим ВВО
    //    vr.msg.automodeDisabledVvo && vr.msg.automodeDisabledNvo  - Не можливий авто.режим НВО | ВВО
    //    vr.msg.automodeDisabledNvo - Не можливий авто.режим НВО

    //    vr.msg.automodeDisabledManual - Не можливий авто.режим НВО/ВВО
    scriptObjectSetup("vr.msg.automodeDisabledVvo");
    scriptObjectSetup("vr.msg.automodeDisabledNvo");
    scriptObjectSetup("vr.msg.automodeDisabledManual");

}
//------------------------------------------------------------------------------------
//!
MultiMsgWidget::~MultiMsgWidget()
{

}
//------------------------------------------------------------------------------------
//!
void MultiMsgWidget::scriptObjectSetup(const QString &scriptObjectName)
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(scriptObjectName);

    if(scriptObject)
    {
        connect(scriptObject, &ScriptObject::dataChanged, [=](){

            if( scriptObject->data() == 1 )
            {
                m_regStateMap[scriptObjectName] = 1;
            } else
            {
                m_regStateMap[scriptObjectName] = 0;
            }
        });

        display();
    }
}
//------------------------------------------------------------------------------------
//!
void MultiMsgWidget::display()
{
    //    vr.msg.automodeDisabledVvo - Не можливий авто. режим ВВО
    //    vr.msg.automodeDisabledVvo && vr.msg.automodeDisabledNvo  - Не можливий авто.режим НВО | ВВО
    //    vr.msg.automodeDisabledNvo - Не можливий авто.режим НВО

    //    vr.msg.automodeDisabledManual - Не можливий авто.режим НВО/ВВО

    if(m_regStateMap["vr.msg.automodeDisabledManual"] == 1)
    {
        setText("Не можливий авто.режим НВО/ВВО");
        setVisible(true);
        emit displayed(true);
    } else if(m_regStateMap["vr.msg.automodeDisabledVvo"] == 1 &&
              m_regStateMap["vr.msg.automodeDisabledNvo"] == 1)
    {
        setText("Не можливий авто.режим НВО | ВВО");
        setVisible(true);
        emit displayed(true);
    } else if(m_regStateMap["vr.msg.automodeDisabledVvo"] == 1)
    {
        setText("Не можливий авто.режим НВО");
        setVisible(true);
        emit displayed(true);
    } else if(m_regStateMap["vr.msg.automodeDisabledNvo"] == 1)
    {
        setText("Не можливий авто.режим ВВО");
        setVisible(true);
        emit displayed(true);
    } else
    {
        setVisible(false);
        emit displayed(false);
    }
}
