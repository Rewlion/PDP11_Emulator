#include "RegistersModel.h"

RegistersModel::RegistersModel(const ::QEmulator& emulator, QObject *parent)
    : QAbstractTableModel(parent)
    , Emulator(emulator)
{
    CachedRegisters = Emulator.GetRegisters();
}

int RegistersModel::rowCount(const QModelIndex &parent) const
{       
    return GetRegistersNumber() + 1/*flagreg*/;
}

int RegistersModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant RegistersModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
        {
            if(index.column() == 0)
            {
                if(index.row() == GetRegistersNumber())
                    return QString("Flags");
                else
                    return QString(GetRegisterName(index.row()));
            }
            else
            {
                const int row = index.row();
                if(row < GetRegistersNumber())
                {
                    return QString("0%1").arg(CachedRegisters.Values[row], 0, 8);
                }
                if(row == GetRegistersNumber())
                {
                    return QString("IPL:%1 T:%2 N:%3 Z:%4 V:%5 C:%6")
                            .arg(CachedRegisters.Flags.InterruptPriority)
                            .arg(CachedRegisters.Flags.Trap)
                            .arg(CachedRegisters.Flags.Sign)
                            .arg(CachedRegisters.Flags.Zero)
                            .arg(CachedRegisters.Flags.Overflow)
                            .arg(CachedRegisters.Flags.Carry);
                }
                else
                    return QString("-1");
            }
        }        
    }

    return QVariant();
}

void RegistersModel::DoUpdate()
{
    CachedRegisters = Emulator.GetRegisters();
    const QModelIndex topLeft = createIndex(0,0);
    const QModelIndex bottomRight = createIndex(GetRegistersNumber()+1, 2);

    emit dataChanged(topLeft, bottomRight);
}
