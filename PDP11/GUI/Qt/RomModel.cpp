#include "RomModel.h"

#include <QtDebug>

RomModel::RomModel(const QEmulator& emulator, QObject *parent)
    : QAbstractTableModel(parent)
    , Emulator(emulator)
{
}

int RomModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 5;
}

int RomModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant RomModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
        {
            const Word pc = Emulator.GetRegister(Register::PC);

            if(index.column() == 0)
            {
                const Word address = pc + index.row() * sizeof(Word);
                const QString format = pc == address ? QString("<==") : QString("");

                return QString("0%1%2").arg(address, 0, 8).arg(format);
            }
            else if(index.column() == 1)
            {
                const std::optional<Word> v = Emulator.ReadMemory(pc + index.row() * sizeof(Word));
                if(v.has_value())
                    return QString("0%1").arg(v.value(), 0, 8);
                else
                    return "Unable to read.";
            }
            else
            {
                return QVariant();
            }
        }

        default:
            return QVariant();
    }

    return QVariant();
}

void RomModel::DoUpdate()
{
    const QModelIndex topLeft = createIndex(0,0);
    const QModelIndex bottomRight = createIndex(rowCount(), columnCount());
    emit dataChanged(topLeft, bottomRight);
}
