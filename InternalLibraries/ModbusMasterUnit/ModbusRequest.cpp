#include "ModbusRequest.h"

//------------------------------------------------------------------------------------
//!
ModbusRequest::ModbusRequest(const ModbusConnectionSettings &connectionSettings,
                             const quint16 &serverAddress,
                             const QModbusPdu::FunctionCode &functionCode,
                             QList< std::tuple<int, QString, QString> > &registerList,
#ifndef CIRCULAR_PROCESSING_REQUEST
                             const int &period,
#endif // CIRCULAR_PROCESSING_REQUEST
                             QObject *parent)
              :QObject(parent),
               m_connectionSettings ( connectionSettings ),
               m_serverAddress ( serverAddress ),
               m_functionCode ( functionCode )
{
    //! Отсортировать адреса по возростающей
    std::sort(registerList.begin(), registerList.end(),
              [] (std::tuple<int, QString, QString> lh,
                  std::tuple<int, QString, QString> rh) {
        return std::get<0>(lh) < std::get<0>(rh);
    });

    int startAddress = std::get<0>( registerList.at(0) );
    int size = std::get<0>( registerList.last() ) - std::get<0>( registerList.first() );

    //--------------------------------------------
    setObjectName(QString("ModbusRequest[%1]servAddr[%2]f[%3]reg[%4:%5]")
                  .arg(connectionSettings.connectionName)
                  .arg(serverAddress)
                  .arg(m_functionCode)
                  .arg(startAddress)
                  .arg(size)
                  );

    //--------------------------------------------
    QModbusDataUnit::RegisterType type = registerTypeFromFunctionCode(m_functionCode);
    //--------------------------------------------
    m_modbusDataUnit = QModbusDataUnit(type,
                                       startAddress,
                                       size);

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
            SEND_TO_LOG( QString("%1 - modbus register connected [%2])")
                         .arg(objectName()).arg(name) );

            m_scriptObjectList.insert(id, scriptObject);

    //        connect(scriptObject, &ScriptObject::dataChanged, [=](){
    //            label->setText(QString("%1").arg(scriptObject->data()));
    //        });
        } else
        {
            SEND_TO_LOG( QString("%1 - ERROR (У регистра нет назначения [%2])")
                         .arg(objectName()).arg(name) );
        }
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
    m_scriptObjectList.clear();

    //-------------------------------------------
    SEND_TO_LOG( QString("%1 - удален").arg(objectName()) );
}
//------------------------------------------------------------------------------------
//!
QModbusDataUnit::RegisterType ModbusRequest::registerTypeFromFunctionCode(const QModbusPdu::FunctionCode &functionCode)
{
    QModbusDataUnit::RegisterType type;

    //! Выполнение запроса
    switch (functionCode)
    {
        case QModbusPdu::Invalid:                   type = QModbusDataUnit::Invalid;            break;
        //-------------------------
        case QModbusPdu::ReadCoils:                 type = QModbusDataUnit::Coils;              break;
        case QModbusPdu::ReadDiscreteInputs:        type = QModbusDataUnit::DiscreteInputs;     break;
        case QModbusPdu::ReadHoldingRegisters:      type = QModbusDataUnit::HoldingRegisters;   break;
        case QModbusPdu::ReadInputRegisters:        type = QModbusDataUnit::InputRegisters;     break;
        case QModbusPdu::WriteSingleCoil:           type = QModbusDataUnit::Coils;              break;
        case QModbusPdu::WriteSingleRegister:       type = QModbusDataUnit::HoldingRegisters;   break;
        //-------------------------
        case QModbusPdu::ReadExceptionStatus:       type = QModbusDataUnit::Invalid;            break;
        case QModbusPdu::Diagnostics:               type = QModbusDataUnit::Invalid;            break;
        case QModbusPdu::GetCommEventCounter:       type = QModbusDataUnit::Invalid;            break;
        case QModbusPdu::GetCommEventLog:           type = QModbusDataUnit::Invalid;            break;
        //-------------------------
        case QModbusPdu::WriteMultipleCoils:        type = QModbusDataUnit::Coils;              break;
        case QModbusPdu::WriteMultipleRegisters:    type = QModbusDataUnit::HoldingRegisters;   break;
        //-------------------------
        case QModbusPdu::ReportServerId:
        case QModbusPdu::ReadFileRecord:
        case QModbusPdu::WriteFileRecord:
        case QModbusPdu::MaskWriteRegister:
        case QModbusPdu::ReadFifoQueue:
        case QModbusPdu::EncapsulatedInterfaceTransport:
        case QModbusPdu::UndefinedFunctionCode:
        default:
            type = QModbusDataUnit::Invalid;
            SEND_TO_LOG( QString("%1 - Попытка выполнить необрабатываемую функцию [%2]")
                         .arg(objectName()).arg(m_functionCode) );
            break;
    }

    return type;
}
//------------------------------------------------------------------------------------
//!
void ModbusRequest::setModbusDataUnit(const QModbusDataUnit &dataUnit)
{
    for (uint i = 0; i < dataUnit.valueCount(); i++)
    {
        const int id          = dataUnit.startAddress() + i;
        //const quint16 value   = dataUnit.value(i);
        const quint16 value   = QString::number(dataUnit.value(i),
                                                dataUnit.registerType() <= QModbusDataUnit::Coils ? 10 : 16).toUShort();

//        const QString entry = tr("Address: %1, Value: %2").arg(id).arg(value);
//        SEND_TO_LOG( QString("%1 - data: %2").arg(objectName()).arg(entry) );

        //-----------------------------------------
        ScriptObject *scriptObject = m_scriptObjectList.value(id, nullptr);

        if(scriptObject)
        {
            scriptObject->setData(value);
        }
    }
}
//------------------------------------------------------------------------------------
//!
