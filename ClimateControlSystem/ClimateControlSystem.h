#ifndef CLIMATECONTROLSYSTEM_H
#define CLIMATECONTROLSYSTEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QString>
#include <QObject>



#include <wiringPi.h>
#include <ds1302.h>
//
#include "Log.h"
#include "DbUnit.h"
#include "ScriptUnit.h"
#include "ModbusMasterUnit.h"
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

//        inline std::shared_ptr<DbUnit>              dbUnit()            { return m_dbUnit; }
//        inline std::shared_ptr<ScriptUnit>          scriptUnit()        { return m_scriptUnit; }
//        inline std::shared_ptr<ModbusMasterUnit>    modbusMasterUnit()  { return m_modbusMasterUnit; }

        inline DbUnit*              dbUnit()            { return &m_dbUnit; }
//        inline ScriptUnit&          scriptUnit()        { return m_scriptUnit; }
//        inline ModbusMasterUnit&    modbusMasterUnit()  { return m_modbusMasterUnit; }

    signals:

    private:
        void setupRpi();

        //! bcdToD: dToBCD:
        //!	BCD decode/encode
        static int bcdToD (unsigned int byte, unsigned int mask);
        static unsigned int dToBcd (unsigned int byte);

        //! ramTest:
        //!	Simple test of the 31 bytes of RAM inside the DS1302 chip
        static int ramTest (void);

        //! setLinuxClock:
        //! Set the Linux clock from the hardware
        static int setLinuxClock (void);

        //! setDSclock:
        //! Set the DS1302 block from Linux time
        static int setDSclock (void);


    private:
//        std::shared_ptr<DbUnit>                 m_dbUnit;
//        std::shared_ptr<ScriptUnit>             m_scriptUnit;
//        std::shared_ptr<ModbusMasterUnit>       m_modbusMasterUnit;

        DbUnit                 m_dbUnit;
        ScriptUnit             m_scriptUnit;
        ModbusMasterUnit       m_modbusMasterUnit;
};
//------------------------------------------------------------------------------------
#endif // CLIMATECONTROLSYSTEM_H
