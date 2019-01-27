#include "EmullatorLogModel.h"

#include <QtDebug>

EmullatorLogModel::EmullatorLogModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

int EmullatorLogModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return Logs.size();
}

int EmullatorLogModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant EmullatorLogModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
    {
        const int row = index.row();
        if(row >= 0 && row < Logs.size())
            return Logs[row].Message;
        else
            return "Wrong Index";
    }
    default:
        return QVariant();
    }
}


void EmullatorLogModel::AddLog(const LogType type, const QString& log)
{
    Logs.push_back({type, log});

    QModelIndex index = createIndex(rowCount()-1, 1);

    emit dataChanged(index, index);
}






