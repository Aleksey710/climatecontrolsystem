#ifndef CHECKAPPUNIQ_H
#define CHECKAPPUNIQ_H
//------------------------------------------------------------------------------------
#include <QCoreApplication>
#include <QSystemSemaphore>
#include <QSharedMemory>
//#include <>
//#include <>



//#include ""
//#include ""
//#include "Log.h"
//#include "svn_version.h"
//---------------------------------------------------
// https://habrahabr.ru/post/173281/
// http://www.evileg.ru/baza-znanij/qt/qt-single-application-zapuskaem-tolko-odin-ekzemplyar-prilozheniya.html
//---------------------------------------------------
/*
    Проверка, что приложение еще не запущено.
    Под linux можно запустить 2 экземпляра приложения под разными пользователями!!!
*/
//---------------------------------------------------
// #include "CheckAppUniq.h"
//------------------------------------------------------------------------------------
static QSharedMemory *sharedMemory = nullptr;
//------------------------------------------------------------------------------------
bool checkAppUniq(const QString &id = "<uniq id>")
{
    // создаём семафор
    QSystemSemaphore semaphore(id, 1);
    // Поднимаем семафор, запрещая другим экземплярам работать с разделяемой памятью
    semaphore.acquire();

#ifndef Q_OS_WIN32
    // в linux/unix разделяемая память не особождается при аварийном завершении приложения,
    // поэтому необходимо избавиться от данного мусора
    QSharedMemory nix_fix_shared_memory(QString("%1_2").arg(id));
    if(nix_fix_shared_memory.attach())
    {
        nix_fix_shared_memory.detach();
    }
#endif

    // Создаём экземпляр разделяемой памяти
    //QSharedMemory sharedMemory(QString("%1_2").arg(id));
    sharedMemory = new QSharedMemory(QString("%1_2").arg(id), QCoreApplication::instance());

    // переменную для проверки ууже запущенного приложения
    bool is_running;

    // пытаемся присоединить экземпляр разделяемой памяти
    // к уже существующему сегменту
    if (sharedMemory->attach())
    {
        // Если успешно, то определяем, что уже есть запущенный экземпляр
        is_running = true;
    } else {
        // В противном случае выделяем 1 байти памяти
        sharedMemory->create(1);
        // И определяем, что других экземпляров не запущено
        is_running = false;
    }

    // Опускаем семафор
    semaphore.release();

    //---------------------------------------------------
    return is_running;
}
//------------------------------------------------------------------------------------
#endif // CHECKAPPUNIQ_H
