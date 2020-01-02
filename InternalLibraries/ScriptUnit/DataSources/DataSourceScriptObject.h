#ifndef DATASOURCESCRIPTOBJECT_H
#define DATASOURCESCRIPTOBJECT_H
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

class DataSourceScriptObject;
//------------------------------------------------------------------------------------
// Для наследников QObject декларировать и использовать только указатель
Q_DECLARE_METATYPE(DataSourceScriptObject*);
//------------------------------------------------------------------------------------
//!
class DataSourceScriptObject : public QObject, protected QScriptable
{
        Q_OBJECT
    public:
        explicit DataSourceScriptObject(const QString &topicName,
                                        const QString &variablePartName,
                                        DataSourceScriptObject *parent = Q_NULLPTR);

        virtual ~DataSourceScriptObject();

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
#endif // DATASOURCESCRIPTOBJECT_H
