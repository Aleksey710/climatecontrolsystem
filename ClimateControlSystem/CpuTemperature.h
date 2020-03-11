#ifndef CPUTEMPERATURE_H
#define CPUTEMPERATURE_H
//------------------------------------------------------------------------------------
#include <QObject>
#include <QTimer>

#include <iostream>
#include <fstream>
#include <string>
//------------------------------------------------------------------------------------
// https://eugene.stormway.ru/works/programmer/cpp/rpitemp
// #include "CpuTemperature.h"
//------------------------------------------------------------------------------------
//!
class CpuTemperature : public QObject
{
        Q_OBJECT
    public:
        CpuTemperature(QObject *parent)
            :QObject(parent)
        {
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this,[=]{

                std::string line;
                std::ifstream infile("/sys/class/thermal/thermal_zone0/temp");
                if (infile.is_open())
                {
                    getline(infile, line);
                    infile.close();
                }

                int value = v_stoi(line, 0);

                tCpuChanged(value / 1000);
            });

            timer->start(1000);
        }

    signals:
        void tCpuChanged(const float &t);

    private:
        inline int v_stoi(std::string &arg, int def)
        {
            try {
                return stoi(arg);
            } catch (...) {
                return def;
            }
        }

};
//------------------------------------------------------------------------------------
#endif // CPUTEMPERATURE_H
