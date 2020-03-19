#include "DataAverager.h"
//------------------------------------------------------------------------------------
//!
DataAverager::DataAverager(const QString &dataScriptObjectName,
                           const QString &averageSizeScriptObjectName,
                           QObject *parent)
             : QObject(parent),
               m_curentIndex ( 0 ),
               m_dataScriptObject ( nullptr ),
               m_dataCount ( 0 )
{
    ScriptObject *scriptObject = ScriptUnit::getScriptObject(averageSizeScriptObjectName);

    if(scriptObject)
    {
        m_valueArray = QVector<double>(scriptObject->data(), 0);
        //m_valueArray.resize(scriptObject->data());
        //m_valueArray.fill(0);
    } else
    {
        m_valueArray = QVector<double>(1, 0);
        //m_valueArray.reserve(1);
        //m_valueArray[0] = 777;
    }

    //----------------------------------------------------------------
    m_dataScriptObject = ScriptUnit::getScriptObject(dataScriptObjectName);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DataAverager::setData);
    timer->start(1000);
}
//------------------------------------------------------------------------------------
//!
DataAverager::~DataAverager()
{

}
//------------------------------------------------------------------------------------
//!
void DataAverager::setData()
{    
    if(m_dataScriptObject)
        m_valueArray[m_curentIndex] = m_dataScriptObject->data();

    m_curentIndex++;

    if(m_curentIndex == m_valueArray.size())
    {
       m_curentIndex = 0;
    }

    //----------------------------------------------
    double value = 0.0;
#ifdef SLIDING_WINDOW
    if(m_dataCount >= m_valueArray.size())
    {
        for (int i = 0; i < m_valueArray.size(); ++i)
        {
            value = value + m_valueArray.at(i);
        }

        value = value/m_valueArray.size();
    } else
    {
        m_dataCount++;
        //------------------------------------------
        for (int i = 0; i < m_dataCount; ++i)
        {
            value = value + m_valueArray.at(i);
        }

        value = value/m_dataCount;
    }

    emit dataUpdate(value);
#else
    m_dataCount++;

    if(m_dataCount >= m_valueArray.size())
    {
        m_dataCount = 0;

        for (int i = 0; i < m_valueArray.size(); ++i)
        {
            value = value + m_valueArray.at(i);
        }

        value = value/m_valueArray.size();

        emit dataUpdate(value);
    }
#endif
}
