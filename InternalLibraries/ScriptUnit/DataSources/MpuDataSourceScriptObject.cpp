#include "MpuDataSourceScriptObject.h"

#include "ScriptUnit.h"
//------------------------------------------------------------------------------------
//!
MpuDataSourceScriptObject::MpuDataSourceScriptObject(const QString &topicName,
                                                     const QString &variablePartName,
                                                     MpuDataSourceScriptObject *parent)
                          :QObject(parent),
                           m_topicName ( topicName ),
                           m_fullName ( variablePartName ),
                           m_value ( 0 ),
                           m_alarmState ( true )

{
    setObjectName(variablePartName);

    if(parent != Q_NULLPTR)
    {
        m_fullName.prepend( QString("%1.").arg(parent->fullName()) );
    }

    m_errorArray = QJsonArray{ QString("Source[%1] - start system!!!").arg(m_fullName) };

    //! Начальная инициализация
    ScriptUnit::m_scriptEngine->evaluate(QString("%1=0;").arg(m_fullName));

//    SEND_TO_LOG( QString("MpuDataSourceScriptObject[%1] - setJsonObject - script:\n"
//                 "%2").arg(fullName()).arg(script) );
}
//------------------------------------------------------------------------------------
//!
MpuDataSourceScriptObject::~MpuDataSourceScriptObject()
{
}
//------------------------------------------------------------------------------------
//! Приход данных от источника данных
void MpuDataSourceScriptObject::setJsonObject(const QJsonObject &jsonObject)
{
//    SEND_TO_LOG( QString("%1 - setJsonObject - %2").arg(m_fullName)
//                 .arg(QString(QJsonDocument(jsonObject).toJson(QJsonDocument::Indented))) );
/*
    //! Пришедшее сообщение - нужного типа
    if( jsonObject.value("type").toInt() != MqttTopicMsgType::JsonData )
    {
        return;
    }

    //-----------------------------------
    QJsonValue errorArrayValue = jsonObject.value("200");

    //! Если сообщение без системных аварий
    //! (ключа 200 нет)
    if(errorArrayValue.isUndefined())
    {
        //-----------------------------------
        //! Флаг востановления после ошибки
        bool isRecovery = false;

        //! Если сообщение востанавливает нормальный статус источника
        //! (было аварийное, пришло нормальное)
        if(m_alarmState == true)
        {
            //! Сохранить нормальный статус в описании состояния
            m_alarmState = false;

            //! Очистить массив аварий
            //! (Признака аварийности достаточно)
            //m_errorArray = QJsonArray();

            //! Установить флаг востановления
            isRecovery = true;
        }

        //-----------------------------------
        //! Флаг изменения данных
        bool isDataChanged = false;

        //! Получить значение переменной источника
        QJsonValue jsonValue = jsonObject.value("0");

        //! При наличии данных - обработать как обычное
        //! (сообщение коректное)
        if( !jsonValue.isUndefined() )
        {            
            const QString jsonValueString = jsonValue.toString();
            const double newValue = jsonValueString.toDouble();

            //! Если новые данные от источника отличаются от старых
            if( m_value != newValue )
            //if( !qFuzzyCompare(value, newValue) )
            {
                //! Сохранить новое значение данных
                m_value = newValue;

                //-----------------------------------
                //! Обновить значение переменной
                const QString script = QString("%1=%2;").arg(m_fullName).arg(jsonValueString);

//                SEND_TO_LOG( QString("MpuDataSourceScriptObject[%1] - setJsonObject - script:\n"
//                                     "%2").arg(fullName()).arg(script) );

                //! Выполнить скрипт
                MqttProcessingUnit::m_scriptEngine->evaluate(script);
                //-----------------------------------

                isDataChanged = true;
            }
        } else
        //! Сообщение без данных
        {
            static const QJsonArray notData { "not data" };
            static const QString scriptNotData = QString("%1=0;").arg(m_fullName);

            m_errorArray = notData;
            m_value = 0;

            //! Выполнить скрипт
            MqttProcessingUnit::m_scriptEngine->evaluate(scriptNotData);

            //-----------------------------------
            isDataChanged = true;

            //-----------------------------------
            SEND_TO_LOG( QString("MpuDataSourceScriptObject[%1] - setJsonObject - сообщение без данных от %1 - ERROR\n"
                                 "%2")
                         .arg(fullName())
                         .arg(QString(QJsonDocument(jsonObject).toJson(QJsonDocument::Indented))) );
        }

        //! Если есть изменения по данным или по статусу
        if(isDataChanged || isRecovery)
        {
            emit dataStateChanged();
        } else
        {
            //! регулярное оповещение с помощью
            //! initForcedNotificationTimer();

            //! надо настроить от источника не пропустит
        }
    } else
    //! Если сообщение по источнику с системной аварией
    {
        static const QJsonArray defaultErrorArray { "default error" };

        QJsonArray curentErrorArray = errorArrayValue.toArray( defaultErrorArray );

        //! Если переход с нормы на аварию
        //! (была норма)
        if(m_alarmState == false)
        {
            //! Установить признак аварии
            m_alarmState = true;

            //! Сохранить массив описаний ошибок
            m_errorArray = curentErrorArray;

            //! Обновить значение переменной
            m_value = 0;

            //-----------------------------------
            //! Обновить значение переменной
            const QString script = QString("%1=0;").arg(m_fullName);

            //! Выполнить скрипт
            MqttProcessingUnit::m_scriptEngine->evaluate(script);

            //! Оповестить об изменении
            emit dataStateChanged();
        } else
        //! Была авария, пришла тоже авария
        {
            //! Если состояние ошибки поменялось
            if(m_errorArray != curentErrorArray )
            {
                //! Сохранить новый массив описаний ошибок
                m_errorArray = curentErrorArray;

                //! Оповестить об изменении
                emit dataStateChanged();
            }
        }

//        } else
//        {
//            //! регулярное оповещение с помощью
//            //! initForcedNotificationTimer();
//        }
    }

*/
}
//------------------------------------------------------------------------------------
//!
