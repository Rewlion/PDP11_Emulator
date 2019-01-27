#ifndef REGISTERSMODEL_H
#define REGISTERSMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include <Qemulator.h>

class RegistersModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RegistersModel(const QEmulator& emulator, QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:

public slots:
    void DoUpdate();

private:
    const QEmulator&     Emulator;
    RegistersInformation CachedRegisters;
};

#endif // REGISTERSMODEL_H
