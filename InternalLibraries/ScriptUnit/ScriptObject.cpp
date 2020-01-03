#include "ScriptObject.h"

#include "ScriptUnit.h"
//------------------------------------------------------------------------------------
//!
ScriptObject::ScriptObject(const QString &name,
                           const double &value,
                           ScriptObject *parent)
             :QObject(parent),
              m_fullName ( name )
{
    setObjectName(name);

    if(parent != Q_NULLPTR)
    {
        m_fullName.prepend( QString("%1.").arg(parent->fullName()) );
    }

    //! Начальная инициализация
    ScriptUnit::scriptEngine()->evaluate(QString("%1=%2;").arg(m_fullName).arg(value));

    //----------------------------------------------------------
    //! test

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){

        double value = QRandomGenerator::global()->bounded(0, 100);

        setData(value);
    });
    timer->start(1000);

    //----------------------------------------------------------
    //SEND_TO_LOG( QString("%1 - создан").arg(objectName()))
}
//------------------------------------------------------------------------------------
//!
ScriptObject::~ScriptObject()
{
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()))
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
