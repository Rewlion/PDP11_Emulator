#include "registerslistmodel.h"

#include "emulator/common/error.h"

namespace Qt::Widgets
{
    namespace
    {
        inline QString ConvertIndexToRegisterName(const QModelIndex& index)
        {
            switch (index.row())
            {
            case EmulatorComponents::RegistersManagement::R1:
                return "R1";
            case EmulatorComponents::RegistersManagement::R2:
                return "R2";
            case EmulatorComponents::RegistersManagement::R3:
                return "R3";
            case EmulatorComponents::RegistersManagement::R4:
                return "R4";
            case EmulatorComponents::RegistersManagement::R5:
                return "R5";
            case EmulatorComponents::RegistersManagement::R6:
                return "R6";
            case EmulatorComponents::RegistersManagement::R7:
                return "R7";
            default:
                throw Common::Error("Wrong index has been provided to a RegistersListModel.", Common::Critical);
            }
        }

        inline EmulatorComponents::RegistersManagement::Register ConvertIndexToRegisterNumber(const QModelIndex& index)
        {
            return EmulatorComponents::RegistersManagement::Register(index.row());
        }
    }

    RegistersListModel::RegistersListModel(QObject* parent)
        : QAbstractListModel(parent)
    {
    }

    int RegistersListModel::rowCount(const QModelIndex &parent) const 
    {
        return RegisterManager.RegistersNumber;
    }

    QVariant RegistersListModel::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= RegisterManager.RegistersNumber)
            return QVariant();

        if (role == Qt::DisplayRole)
        {
            const QString regName = ConvertIndexToRegisterName(index);
            const QString valueInRegister = QString::number(RegisterManager.GetRegister(ConvertIndexToRegisterNumber(index)), 10);

            return  regName + ": " + valueInRegister;;
        }
        else
            return QVariant();
    }
}