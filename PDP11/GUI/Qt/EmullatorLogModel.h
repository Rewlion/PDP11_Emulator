#ifndef EMULLATORLOGMODEL_H
#define EMULLATORLOGMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include <Common/Logs/LogType.h>

#include <QVector>

class EmullatorLogModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit EmullatorLogModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:

public slots:
    void AddLog(const LogType type, const QString& log);

private:
    struct LogMessage
    {
        LogType Type;
        QString Message;
    };

private:
    QVector<LogMessage> Logs;
};

#endif // EMULLATORLOGMODEL_H
