#ifndef MODBUSLOG_H
#define MODBUSLOG_H
//------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
//------------------------------------------------------------------------------------
inline static void modbus_log(const char *msg, ...)
{


    va_list args;
    va_start(args, msg);

    char modbus_buffer [200];
    snprintf(modbus_buffer, 100, msg, args);
    //qDebug(msg, args);

    //fprintf(log, "File: \"%s\", Line: %d\n", __File__, __Line__);

    puts (modbus_buffer);

    va_end(args);

    //LOG(INFO) << QString(modbus_buffer);
    //SEND_TO_LOG(QString(modbus_buffer));
}

//snprintf ( modbus-buffer, 100, "The half of %d is %d", 60, 60/2 );

#define MODBUS_LOG(...) modbus_log(__VA_ARGS__);

//#define MODBUS_LOG(msg, ...) fprintf(stderr, msg);


//------------------------------------------------------------------------------------
#endif // MODBUSLOG_H
