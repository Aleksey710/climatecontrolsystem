#ifndef CLIMATECONTROLSYSTEM_H
#define CLIMATECONTROLSYSTEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QString>
#include <QObject>

#include <functional>
//
/*
#ifndef Q_OS_WIN
    #ifdef __arm__
        #include <wiringPi.h>
        #include <ds1302.h>
    #endif
#endif
*/
//
#include "Log.h"
#include "DbUnit.h"
#include "ScriptUnit.h"
#include "ModbusMasterUnit.h"
#include "CustomFunctions.h"
//#include ".h"
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

        inline DbUnit*              dbUnit()            { return &m_dbUnit; }

    signals:

    private:
        void setupRpi();


    private:
        DbUnit                 m_dbUnit;
        ScriptUnit             m_scriptUnit;
        ModbusMasterUnit       m_modbusMasterUnit;
};
//------------------------------------------------------------------------------------
#endif // CLIMATECONTROLSYSTEM_H
