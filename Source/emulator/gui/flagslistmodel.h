#pragma once

#include <emulator/cpu/RegisterManager.h>

#include <thirdparty/Qt/QtCore/qabstractitemmodel.h>

namespace Qt::Widgets
{
    class FlagsListModel : public QAbstractListModel
    {
    public:
        FlagsListModel(QObject* parent = nullptr);

        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        inline void SetFlags(const byte& flags)
        {
            Flags = flags;
        }
    private:
        byte Flags;
    };
}