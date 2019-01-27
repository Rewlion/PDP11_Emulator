#ifndef MEMORYDUMPWIDGET_H
#define MEMORYDUMPWIDGET_H

#include <QWidget>
#include <Qemulator.h>

namespace Ui {
class MemoryDumpWidget;
}

class MemoryDumpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MemoryDumpWidget(const QEmulator& emulator, QWidget *parent = nullptr);
    ~MemoryDumpWidget();

signals:
    void OnDump(const Word address);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MemoryDumpWidget *ui;
    const QEmulator&      Emulator;
};

#endif // MEMORYDUMPWIDGET_H
