#ifndef MEMORYDUMPMODEL_H
#define MEMORYDUMPMODEL_H

#include <QObject>
#include <QAbstractTableModel>

#include "Qemulator.h"
#include <QVector>

class MemoryDumpModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MemoryDumpModel(const QEmulator& emulator, QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

signals:

public slots:
    void Dump(const Word addressBegin);

private:
    struct DumpInfo
    {
        Word Address = 0;
        Word Value   = 0;
    };

private:
    const QEmulator&  Emulator;
    QVector<DumpInfo> Dumps;
};

#endif // MEMORYDUMPMODEL_H
