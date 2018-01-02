#pragma once

#include <emulator/cpu/RegisterManager.h>

#include <thirdparty/Qt/QtCore/qabstractitemmodel.h>

namespace Qt::Widgets
{
    class RegistersListModel : public QAbstractListModel
    {
    public:
        RegistersListModel(QObject* parent = nullptr);

        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        inline void SetRegisterManager(const EmulatorComponents::RegistersManagement::RegisterManager& registerManager)
        {
            RegisterManager = registerManager;
        }
    private:
        EmulatorComponents::RegistersManagement::RegisterManager RegisterManager;
    };
}