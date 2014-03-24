#include "mainwindow.h"
#include <QApplication>
#include <QTime>
 #include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    for(int i =0; i < 100; i++)
        w.moveAgents();
    return a.exec();

}

