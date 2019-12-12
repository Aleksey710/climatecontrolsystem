#ifndef CHECKAPPUNIQ_H
#define CHECKAPPUNIQ_H
//------------------------------------------------------------------------------------
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
bool checkAppUniq()
{
    QSystemSemaphore semaphore("<uniq id>", 1);  // создаём семафор
    semaphore.acquire(); // Поднимаем семафор, запрещая другим экземплярам работать с разделяемой памятью

#ifndef Q_OS_WIN32
    // в linux/unix разделяемая память не особождается при аварийном завершении приложения,
    // поэтому необходимо избавиться от данного мусора
    QSharedMemory nix_fix_shared_memory("<uniq id 2>");
    if(nix_fix_shared_memory.attach())
    {
        nix_fix_shared_memory.detach();
    }
#endif

    QSharedMemory sharedMemory("<uniq id 2>");  // Создаём экземпляр разделяемой памяти
    bool is_running;            // переменную для проверки ууже запущенного приложения
    if (sharedMemory.attach()){ // пытаемся присоединить экземпляр разделяемой памяти
                                // к уже существующему сегменту
        is_running = true;      // Если успешно, то определяем, что уже есть запущенный экземпляр
    }else{
        sharedMemory.create(1); // В противном случае выделяем 1 байти памяти
        is_running = false;     // И определяем, что других экземпляров не запущено
    }
    semaphore.release();        // Опускаем семафор

    //---------------------------------------------------
    return is_running;
}
//------------------------------------------------------------------------------------
#endif // CHECKAPPUNIQ_H
