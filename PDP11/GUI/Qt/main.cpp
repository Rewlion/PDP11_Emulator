#include "MainWindow.h"
#include <QApplication>

#include <Common/Logs/Logs.h>
#include "QLog.h"

BaseLog* Logger;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger = new QLog;

    MainWindow w;
    w.show();

    return a.exec();
}
