#include "MemoryDumpModel.h"

#include <QtDebug>

MemoryDumpModel::MemoryDumpModel(const QEmulator& emulator, QObject *parent)
    : QAbstractTableModel(parent)
    , Emulator(emulator)
{
    Dumps.resize(rowCount());
}


int MemoryDumpModel::rowCount(const QModelIndex &parent) const
{
    return 20;
}

int MemoryDumpModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant MemoryDumpModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
        {
            if(index.column() == 0)
                return QString("%1").arg(Dumps[index.row()].Address, 0, 8);
            else
                return QString("%1").arg(Dumps[index.row()].Value, 0, 8);
        }
    default:
        return QVariant();
    }
}

void MemoryDumpModel::Dump(const Word addressBegin)
{
    int n = rowCount();
    const size_t end = addressBegin + n > GetSimulatedMachineMemorySize() ? GetSimulatedMachineMemorySize() : addressBegin + n;

    n = end - addressBegin;
    for(int i = 0; i < n; ++i)
    {
        DumpInfo d;
        d.Address = addressBegin + i * sizeof(Word);
        std::optional<Word> v = Emulator.ReadMemory(d.Address);
        if(v.has_value())
        {
            d.Value = v.value();
        }
        else
        {
            d.Address = 0;
            d.Value = 0;
        }

        Dumps[i] = d;
    }

    QModelIndex topLeft = createIndex(0,0);
    QModelIndex bottomRight = createIndex(rowCount()-1,columnCount()-1);

    emit dataChanged(topLeft, bottomRight);
}


