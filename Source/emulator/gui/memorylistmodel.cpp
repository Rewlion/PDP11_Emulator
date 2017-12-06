#include "memorylistmodel.h"

#include <emulator/common/bitoperations.h>
#include <emulator/common/error.h>
#include <emulator/memory/MemoryManager.h>

namespace Qt::Widgets
{
    namespace
    {
        inline size_t ConvertIndexToCorrectOffset(const QModelIndex& index)
        {
            return index.row() * sizeof(word);
        }
    }

    MemoryListModel::MemoryListModel(QObject* parent)
        : QAbstractListModel(parent)
        , Memory(nullptr)
        , AllocatedMemorySize(0)
    {
    }

    int MemoryListModel::rowCount(const QModelIndex &parent) const
    {
        return AllocatedMemorySize / sizeof(word);
    }

    QVariant MemoryListModel::data(const QModelIndex &index, int role) const
    {
        if (index.row() < 0 || index.row() >= (AllocatedMemorySize / sizeof(word)))
            return QVariant();

        if (role == Qt::DisplayRole)
        {
            const size_t offset = ConvertIndexToCorrectOffset(index);
            const QString addressStr = QString::number(EmulatorComponents::MemoryManagement::getROMBegining() + offset, 16);
            const word valueInAddress = *reinterpret_cast<const word*>(Memory + offset);
            const QString valueStr = QString::number(valueInAddress, 8);

            return  QString("0x%1: %2").arg(addressStr).arg(valueStr);
        }
        else
            return QVariant();
    }
}