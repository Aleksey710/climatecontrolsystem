#ifndef MPUDATASOURCESCRIPTOBJECT_H
#define MPUDATASOURCESCRIPTOBJECT_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QVariant>
#include <QList>
#include <QScriptValue>
#include <QScriptEngine>
#include <QScriptable>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
//#include <>
//#include <>


//#include ""
//#include ""
//#include ""
#include "Log.h"
//#include "AlarmStateDescription.h"
//#include "MqttTopicMsgType.h"

//------------------------------------------------------------------------------------
//class MqttProcessingUnit;

class MpuDataSourceScriptObject;
//------------------------------------------------------------------------------------
// Для наследников QObject декларировать и использовать только указатель
Q_DECLARE_METATYPE(MpuDataSourceScriptObject*);
//------------------------------------------------------------------------------------
//!
class MpuDataSourceScriptObject : public QObject, protected QScriptable
{
        Q_OBJECT
    public:
        explicit MpuDataSourceScriptObject(const QString &topicName,
                                           const QString &variablePartName,
                                           MpuDataSourceScriptObject *parent = Q_NULLPTR);

        virtual ~MpuDataSourceScriptObject();

        inline QString topicName() const
            { return m_topicName; }

        inline QString fullName() const
            { return m_fullName; }
        //--------------------------------------------------
        //! Приход данных от источника данных
        void setJsonObject(const QJsonObject &jsonObject);

        //--------------------------------------------------
        Q_INVOKABLE inline double data() const
            { return m_value; }

        Q_INVOKABLE inline void setData(const double &data)
            { m_value = data; }

        Q_INVOKABLE inline bool alarmState() const
            { return m_alarmState; }

        Q_INVOKABLE inline QJsonArray errorArray() const
            { return m_errorArray; }

    signals:
        Q_INVOKABLE void dataStateChanged();

    protected:
        QString     m_topicName;

        QString     m_fullName;

        double      m_value;

        //! Массив описаний системных ошибок
        //! (при отсутствии системной аварии - пуст)
        QJsonArray  m_errorArray;

        //! true - системная авария
        //! false - отсутствие системной аварии
        bool        m_alarmState;
};
//------------------------------------------------------------------------------------
#endif // MPUDATASOURCESCRIPTOBJECT_H
