#ifndef MODBUSPARTNER_H
#define MODBUSPARTNER_H
//------------------------------------------------------------------------------------
#include <modbus.h>
#include <QVector>
#include <QString>
#include <QMap>
#include <QThread>
//#include <>
//#include <>
//#include <>


//#include ""
//#include ""
#include "ModbusConnectionAddress.h"
#include "AbstractFactory.h"

#include "Log.h"

#include "ModbusCore.h"
#include "ModbusRTU.h"
#include "ModbusASCII.h"
#include "ModbusTCP.h"

#include "ModbusData.h"
#include "ModbusConsts.h"
//------------------------------------------------------------------------------------
//!
class ModbusPartner : public QObject
{
        Q_OBJECT

        //! Сколько раз будет сделана запись в лог о переинициализации
        //! до начала маскирования
        static const int MAX_REINIT_NUMBER_WRITING = 5;

    public:
        explicit ModbusPartner(const QString &coreType,
                               const ModbusConnectionAddress &modbusConnectionAddress,
                               QObject *parent = nullptr);

        virtual ~ModbusPartner();

        virtual void reinit();

        inline virtual int setDebug(int flag)
            { return modbus_set_debug(m_modbusCore->modbus(), flag); }

        inline uint32_t getResponseTimeoutUsec()
            {
                uint32_t to_sec;
                uint32_t to_usec;
                modbus_get_response_timeout(m_modbusCore->modbus(), &to_sec, &to_usec);
                return to_sec * 1000 + to_usec;
            }

        inline int setResponseTimeoutUsec(uint32_t timeout)
            { return modbus_set_response_timeout(m_modbusCore->modbus(), 0, timeout); }

        inline int setSlaveAddress(int address)
            { return modbus_set_slave(m_modbusCore->modbus(), address); }

        //------------------------------------------------------------------------------------

    protected:
        ModbusCore              *m_modbusCore;
        QString                 m_coreType;
        ModbusConnectionAddress m_modbusConnectionAddress;

        QThread                 m_modbusCoreThread;

    private:
        AbstractFactory<QString, ModbusCore, ModbusConnectionAddress> m_modbusCoreFactory;

        //------------------------------------------------------------------------------------
        //! счетчик переинициализаций
        int m_reinitCount;

        //! Маскирование логирования
        bool m_maskLogReinit;
};
//------------------------------------------------------------------------------------
#endif // MODBUSPARTNER_H
