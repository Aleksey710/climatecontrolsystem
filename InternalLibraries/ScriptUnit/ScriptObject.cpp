#include "ScriptObject.h"

#include "ScriptUnit.h"
//------------------------------------------------------------------------------------
//!
ScriptObject::ScriptObject(const QString &name,
                           const double &__value,
                           ScriptObject *parent)
             :QObject(parent),
              m_fullName ( name ),
              m_dataType ( "double" ),
              value ( __value )

{
    setObjectName(name);

    if(parent != Q_NULLPTR)
    {
        m_fullName.prepend( QString("%1.").arg(parent->fullName()) );
    }

    //----------------------------------------------------------
    //! test
/*
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){

        double value = QRandomGenerator::global()->bounded(0, 100);

        setData(value);
    });
    timer->start(1000);
*/
    //----------------------------------------------------------
    //SEND_TO_LOG( QString("ScriptObject[%1] - создан").arg(objectName()))
}
//------------------------------------------------------------------------------------
//!
ScriptObject::ScriptObject(const QString &name,
                           const QString &__stringValue,
                           ScriptObject *parent)
             :QObject(parent),
              m_fullName ( name ),
              m_dataType ( "string" ),
              stringValue ( __stringValue )

{
    setObjectName(name);

    if(parent != Q_NULLPTR)
    {
        m_fullName.prepend( QString("%1.").arg(parent->fullName()) );
    }
    //----------------------------------------------------------
    //SEND_TO_LOG( QString("ScriptObject[%1] - создан").arg(objectName()))
}
//------------------------------------------------------------------------------------
//!
ScriptObject::~ScriptObject()
{
    SEND_TO_LOG( QString("ScriptObject[%1] - удален").arg(m_fullName))
}
//------------------------------------------------------------------------------------
//!
ScriptObject* ScriptObject::getChildren(const QString &name)
{
    QList<QObject*> childrenList = children();

    ScriptObject *scriptObject = nullptr;

    for (int i = 0; i < childrenList.size(); ++i)
    {
        scriptObject = static_cast<ScriptObject*>( childrenList.at(i) );

        if(scriptObject->objectName() == name)
        {
            return scriptObject;
        }
    }

    return nullptr;
}
//------------------------------------------------------------------------------------
//!
