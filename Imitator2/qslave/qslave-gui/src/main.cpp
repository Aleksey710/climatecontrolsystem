//------------------------------------------------------------------------------
//
//
//
//
//
//------------------------------------------------------------------------------

#include "mainwindow.h"
#include "mainwindowATOR.h"
#include <QApplication>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    MainWindowATOR w;
    w.show();

    return a.exec();
}