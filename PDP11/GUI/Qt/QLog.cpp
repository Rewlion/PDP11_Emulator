#include "QLog.h"

#include <string>
#include <QtDebug>

QLog::QLog(QObject *parent) : QObject(parent)
{

}

void QLog::Log(const LogType type, const std::string_view message)
{
    emit OnLog(type, QString::fromStdString(std::string(message)));
}
