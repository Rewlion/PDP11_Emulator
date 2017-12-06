#include "flagslistmodel.h"

#include <emulator/common/bitoperations.h>
#include <emulator/common/error.h>

namespace Qt::Widgets
{
    namespace
    {
        inline QString ConvertIndexToFlagName(const QModelIndex& index)
        {
            switch (index.row())
            {
            case EmulatorComponents::RegistersManagement::Carry:
                return "Carry";
            case EmulatorComponents::RegistersManagement::Overflow:
                return "Overflow";
            case EmulatorComponents::RegistersManagement::Zero:
                return "Zero";
            case EmulatorComponents::RegistersManagement::Sign:
                return "Sign";
            case EmulatorComponents::RegistersManagement::Trap:
                return "Trap";
            default:
                throw Common::Error("Wrong index has been provided to a FlagsListModel.", Common::Critical);
            }
        }
    }

    FlagsListModel::FlagsListModel(QObject* parent)
        : QAbstractListModel(parent)
    {
    }

    int FlagsListModel::rowCount(const QModelIndex &parent) const
    {
        return EmulatorComponents::RegistersManagement::RegisterManager::FlagsNumber;
    }

    QVariant FlagsListModel::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= EmulatorComponents::RegistersManagement::RegisterManager::FlagsNumber)
            return QVariant();

        if (role == Qt::DisplayRole)
        {
            const QString flagName = ConvertIndexToFlagName(index);
            const QString bitValue = QString::number(Common::GetBit(Flags, index.row()), 10);

            return  flagName + ": " + bitValue;;
        }
        else
            return QVariant();
    }
}