#include "mainwindow.h"
#include <QGuiApplication>
#include <client.h>
int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    MainWindow w;
    w.show();
    //client* cli = new client();
    //cli->connectTo();
    return a.exec();
}
