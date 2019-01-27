#ifndef QLOGGER_H
#define QLOGGER_H

#include <QObject>

#include <Common/Logs/BaseLog.h>

class QLog : public QObject, public BaseLog
{
    Q_OBJECT
public:
    explicit QLog(QObject *parent = nullptr);

    virtual void Log(const LogType type, const std::string_view message) override;

signals:
    void OnLog(const LogType type, const QString& message);

public slots:
};

#endif // QLOGGER_H
