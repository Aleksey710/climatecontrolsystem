#include "ModbusRequest.h"

//------------------------------------------------------------------------------------
//!
ModbusRequest::ModbusRequest(const ModbusConnectionSettings &connectionSettings,
                             const quint16 &serverAddress,
                             const int &functionCode,
                             QList< std::tuple<int, QString, QString> > &registerList,
#ifndef CIRCULAR_PROCESSING_REQUEST
                             const int &period,
#endif // CIRCULAR_PROCESSING_REQUEST
                             QObject *parent)
              :QObject(parent),
               m_connectionSettings ( connectionSettings ),
               m_serverAddress ( serverAddress ),
               m_functionCode ( functionCode ),
               m_deviceScriptObject ( nullptr ),
               m_lastDeviceState ( 0 )
{
    //! Отсортировать адреса по возростающей
    std::sort(registerList.begin(), registerList.end(),
              [] (std::tuple<int, QString, QString> lh,
                  std::tuple<int, QString, QString> rh) {
        return std::get<0>(lh) < std::get<0>(rh);
    });

    m_startAddress = std::get<0>( registerList.at(0) );
    m_number       = std::get<0>( registerList.last() ) - std::get<0>( registerList.first() ) + 1;

    //--------------------------------------------
    setObjectName(QString("ModbusRequest[%1]servAddr[%2]f[%3]reg[%4:%5]")
                  .arg(connectionSettings.connectionName)
                  .arg(serverAddress)
                  .arg(m_functionCode)
                  .arg(m_startAddress)
                  .arg(m_number)
                  );

    //--------------------------------------------

    for (int i = 0; i < registerList.size(); ++i)
    {
        std::tuple<int, QString, QString> reg = registerList.at(i);

        const int       id      = std::get<0>( reg );
        const QString   name    = std::get<1>( reg );
        //const QString   title   = std::get<2>( reg );

        ScriptObject *scriptObject = ScriptUnit::getScriptObject(name);

        if(scriptObject)
        {
            SEND_TO_LOG( QString("%1 - modbus register connected [%2]")
                         .arg(objectName()).arg(name) );

            m_scriptObjectList.insert(id, scriptObject);
        } else
        {
            SEND_TO_LOG( QString("%1 - ERROR (У регистра нет назначения [%2])")
                         .arg(objectName()).arg(name) );
        }
    }

    //--------------------------------------------
    QStringList partNameList = std::get<1>( registerList.at(0) ).split(".");

    QString deviceScriptObjectName = QString("%1.%2.device").arg(partNameList.at(0)).arg(partNameList.at(1));

    m_deviceScriptObject = ScriptUnit::getScriptObject(deviceScriptObjectName);

    if( m_deviceScriptObject )
    {
        SEND_TO_LOG( QString("%1 - modbus device connected [%2]")
                     .arg(objectName()).arg(deviceScriptObjectName) );
    } else
    {
        SEND_TO_LOG( QString("%1 - ERROR (У устройства нет назначения [%2])")
                     .arg(objectName()).arg(deviceScriptObjectName) );
    }
    //--------------------------------------------
#ifndef CIRCULAR_PROCESSING_REQUEST
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        emit wantExecuteQuery(this);
    });
    timer->start(period);
#else

#endif // CIRCULAR_PROCESSING_REQUEST

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - создан").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
ModbusRequest::~ModbusRequest()
{
    m_deviceScriptObject = nullptr;

    QHashIterator<quint16, ScriptObject*> i(m_scriptObjectList);
    while (i.hasNext())
    {
        i.next();

        m_scriptObjectList.remove(i.key());
    }

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
template < typename T >
T* ModbusRequest::modbusData()
{
    T* dest = (T*) malloc(m_number * sizeof(T));

    //---------------------------------------------------------
    memset(dest, 0, m_number * sizeof(T)); // ???

    //---------------------------------------------------------
    QHashIterator<quint16, ScriptObject*> i(m_scriptObjectList);

    while (i.hasNext())
    {
        i.next();

        const quint16 addr          = i.key();
        ScriptObject *scriptObject  = i.value();

        if(scriptObject)
        {
            dest[addr - m_startAddress] = static_cast<T>(scriptObject->data()) ;

//            SEND_TO_LOG( QString("%1 - modbusData : [%2]-[%3]")
//                         .arg(objectName())
//                         .arg(scriptObject->fullName())
//                         .arg(dest[addr - m_startAddress]) );
        }
    }

    return dest;
}
//------------------------------------------------------------------------------------
//! Комплексная обработка записи значений в скриптовые регистры
template < typename T >
void ModbusRequest::setModbusDataComplex(T *values, int deviceState)
{
    //qDebug() << "ModbusRequest::setModbusData" << dataUnit.values();
    // [ 0] - начальное состояние
    // [-1] - обрыв
    // [ 1] - работа
    int stateCod = ( (m_lastDeviceState == 1) ? 1 : 0 ) +
                   ( (deviceState == 1)       ? 2 : 0 );

    //-----------------------------------------------
    //! Состояние устройства не менялось
    switch (stateCod)
    {
        // Устройство не работало и не работает
        case 0:
            //!
            break;
        // Обрыв связи - Сначала изменить состояние устройства, потом данные
        case 1:
            if(m_deviceScriptObject)
                { m_deviceScriptObject->setData(deviceState); }
            //----------------------------------
            setModbusData(values, deviceState);
            break;
        // Востановление связи - Сначала изменить данные, потом состояние устройства
        case 2:
            setModbusData(values, deviceState);
            //----------------------------------
            if(m_deviceScriptObject)
                { m_deviceScriptObject->setData(deviceState); }
            break;
        // Нормальная работа (работало и работает) - изменить данные
        case 3:
            setModbusData(values, deviceState);
            break;
        default:
            break;
    }
}
//------------------------------------------------------------------------------------
//! Запись значений в скриптовые регистры
template < typename T >
void ModbusRequest::setModbusData(T *values, int deviceState)
{
    QHashIterator<quint16, ScriptObject*> i(m_scriptObjectList);

    while (i.hasNext())
    {
        i.next();

        const int id = i.key();
        ScriptObject *scriptObject = i.value();

        uint16_t value = (deviceState == 1) ?
                            values[id - m_startAddress] :
                                //---------------------------------------------
                                //std::numeric_limits<uint16_t>::max(); //65535
                                //---------------------------------------------
                                0
                                //---------------------------------------------
                                ;

        //--------------------------------------------------
        QMetaObject::invokeMethod(scriptObject,
                                  "setData",
                                  Qt::QueuedConnection,
                                  //Qt::DirectConnection,
                                  Q_ARG(double, value));

        //scriptObject->setData( value);
        //--------------------------------------------------
        SEND_TO_LOG( QString("%1 - setModbusData : [%2]-[%3] device(%4)")
                     .arg(objectName())
                     .arg(scriptObject->fullName())
                     .arg(value)
                     .arg( (deviceState == 1) ? "connect" : "disconnect" ) );
    }
}
//------------------------------------------------------------------------------------
//! https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function
//! Явная инстанциация конкретных экземпляров функции.
//! Без явного определения - не считает нужным создавать
//! В данном случае (Колличество инстанциаций известно заранее) предпочтительнее перед
//! перемещением кода реализации в заголовочный файл.
template void ModbusRequest::setModbusDataComplex(uint8_t *values,      int deviceState);
template void ModbusRequest::setModbusDataComplex(uint16_t *values,     int deviceState);
template void ModbusRequest::setModbusDataComplex(int *values,          int deviceState);

template void ModbusRequest::setModbusData(uint8_t *values,             int deviceState);
template void ModbusRequest::setModbusData(uint16_t *values,            int deviceState);
template void ModbusRequest::setModbusData(int *value,                  int deviceState);

template uint8_t*   ModbusRequest::modbusData();
template uint16_t*  ModbusRequest::modbusData();
template int*       ModbusRequest::modbusData();
//------------------------------------------------------------------------------------
