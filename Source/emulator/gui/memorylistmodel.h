#pragma once

#include <emulator/common/types.h>
#include <emulator/common/error.h>

#include <memory>

#include <thirdparty/Qt/QtCore/qabstractitemmodel.h>

namespace Qt::Widgets
{
    class MemoryListModel : public QAbstractListModel
    {
    public:
        MemoryListModel(QObject* parent = nullptr);

        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        inline void ResetMemory() const
        {
            Memory = nullptr;
            AllocatedMemorySize = 0;
        }

        inline void SetMemoryPointer(const byte* const memory, const size_t allocatedMemorySize) const
        {
            Memory = memory;
            AllocatedMemorySize = allocatedMemorySize;
        }
    private:
        mutable byte const* Memory;
        mutable size_t AllocatedMemorySize;
    };
}
//Todo: in case of uploading new program , set nullptr here first! Then emit the signal to cpu!
