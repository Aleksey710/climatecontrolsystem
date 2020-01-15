#ifndef VERSIONS_H
#define VERSIONS_H
//------------------------------------------------------------------------------------
#include <QString>
#include <QDebug>
//#include <>
//#include <>


//#include ""
//#include ""
#include "Log.h"
//------------------------------------------------------------------------------------
//#include "versions.h"
//------------------------------------------------------------------------------------
inline QString allVersion()
{
    return QString("\r\n"
       "********************************************************************\n"
       "****                         VERSIONS                           ****\n"
       "********************************************************************\n"
       "Qt..................: %1 \n"
       "OS..................: %2 \n"
       "Make OS.............: %3 \n"
       "App.................: %4 \n"
       //"SVN.................: %5 \n"
       "Date time created...: %6 \n"
       "--------------------------------------------------------------------\n"
       //"Build version.......: %7 \n"
       "********************************************************************"
       )
       .arg( QString("%1.%2.%3")        .arg(QT_VERSION_MAJOR).arg(QT_VERSION_MINOR).arg(QT_VERSION_PATCH) )            // 1
       .arg( QString("%1 %2 %3 %4")     .arg(DISTRIBUTION1).arg(DISTRIBUTION2).arg(DISTRIBUTION3).arg(DISTRIBUTION4) )  // 2
       .arg( QString("%1 %2 Kernel: %3").arg(QMAKE_HOST_os).arg(QMAKE_HOST_arch).arg(QMAKE_HOST_version) )              // 3
       .arg( QString("%1.%2.%3")        .arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD) )                     // 4
       //.arg( SVNVersionString() )                                                                                       // 5
       .arg( QString("%1 %2")           .arg(DATE_CREATED).arg(TIME_CREATED) )                                          // 6
       //.arg( QString("%1")              .arg(BUILD_VERSION_CREATED) )                                                   // 7
       ;
}
//------------------------------------------------------------------------------------
#endif // VERSIONS_H
