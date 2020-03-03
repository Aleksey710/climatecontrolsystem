#ifndef CLIMATECONTROLSYSTEM_H
#define CLIMATECONTROLSYSTEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
#include <QProcess>
#include <QString>
#include <QObject>

#include <functional>
// /*
#ifdef __arm__
    #include <wiringPi.h>
#endif
// */
#include "Log.h"
#include "DbUnit.h"
#include "ScriptUnit.h"
#include "ModbusMasterUnit.h"
#include "CustomFunctions.h"
#include "Password.h"
//#include ".h"
//#include ".h"
//#include ".h"
//------------------------------------------------------------------------------------
//!
class ClimateControlSystem : public QObject
{
        Q_OBJECT
    public:
        explicit ClimateControlSystem(QObject *parent = nullptr);
        virtual ~ClimateControlSystem();

        inline DbUnit* dbUnit()
            { return &m_dbUnit; }

    signals:

    private slots:
        void setPassword();


    private:
        void coolerSetup();

    private:
        DbUnit                 m_dbUnit;
        ScriptUnit             m_scriptUnit;
        ModbusMasterUnit       m_modbusMasterUnit;
};
//------------------------------------------------------------------------------------
#endif // CLIMATECONTROLSYSTEM_H
