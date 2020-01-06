#ifndef CLIMATECONTROLSYSTEM_H
#define CLIMATECONTROLSYSTEM_H
//------------------------------------------------------------------------------------
//#include <>
//#include <>
//#include <>
#include <QString>
#include <QObject>



#include "Log.h"
#include "MainDisplayWidget.h"
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

    signals:

    private:
        std::shared_ptr<DbUnit>                 m_dbUnit;
        std::shared_ptr<ScriptUnit>             m_scriptUnit;
        std::shared_ptr<ModbusMasterUnit>       m_modbusMasterUnit;
        std::shared_ptr<MainDisplayWidget>      m_mainDisplayWidget;

//        DbUnit             *m_dbUnit;
//        ScriptUnit         *m_scriptUnit;
//        ModbusMasterUnit   *m_modbusMasterUnit;

//        MainDisplayWidget  *m_mainDisplayWidget;

};
//------------------------------------------------------------------------------------
#endif // CLIMATECONTROLSYSTEM_H
