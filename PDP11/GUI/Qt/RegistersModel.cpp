#include "RegistersModel.h"

RegistersModel::RegistersModel(const ::QEmulator& emulator, QObject *parent)
    : QAbstractTableModel(parent)
    , Emulator(emulator)
{
    CachedRegisters = Emulator.GetRegisters();
}

int RegistersModel::rowCount(const QModelIndex &parent) const
{       
    return GetRegistersNumber();
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
                return QString(GetRegisterName(index.row()));
            }
            else
            {
                const int row = index.row();
                if(row < GetRegistersNumber())
                    return QString("0%1").arg(CachedRegisters.Values[row], 0, 8);
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
    const QModelIndex bottomRight = createIndex(GetRegistersNumber(), 2);

    emit dataChanged(topLeft, bottomRight);
}
