#ifndef CLIMATECONTROLSYSTEM_H
#define CLIMATECONTROLSYSTEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QString>
#include <QObject>



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

        inline std::shared_ptr<DbUnit>              dbUnit()            { return m_dbUnit; }
        inline std::shared_ptr<ScriptUnit>          scriptUnit()        { return m_scriptUnit; }
        inline std::shared_ptr<ModbusMasterUnit>    modbusMasterUnit()  { return m_modbusMasterUnit; }

    signals:

    private:
        std::shared_ptr<DbUnit>                 m_dbUnit;
        std::shared_ptr<ScriptUnit>             m_scriptUnit;
        std::shared_ptr<ModbusMasterUnit>       m_modbusMasterUnit;
};
//------------------------------------------------------------------------------------
#endif // CLIMATECONTROLSYSTEM_H
