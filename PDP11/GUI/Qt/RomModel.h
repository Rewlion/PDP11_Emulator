#ifndef ROMMODEL_H
#define ROMMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include "Qemulator.h"

class RomModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RomModel(const QEmulator& emulator, QObject *parent = nullptr);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:


public slots:
    void DoUpdate();

private:
    void ResetCache();

private:
    const QEmulator& Emulator;
};

#endif // ROMMODEL_H
