#include "MemoryDumpWidget.h"
#include "MemoryDumpModel.h"
#include "ui_memorydumpwidget.h"
#include <Common/Types.h>
#include <QLineEdit>
#include <QTableView>
#include <QtDebug>

MemoryDumpWidget::MemoryDumpWidget(const QEmulator& emulator, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MemoryDumpWidget)
    , Emulator(emulator)
{
    ui->setupUi(this);

    auto* view = findChild<QTableView*>("memoryDump");
    auto* model = new MemoryDumpModel(Emulator);
    view->setModel(model);

    connect(this, &MemoryDumpWidget::OnDump, model, &MemoryDumpModel::Dump);
}

MemoryDumpWidget::~MemoryDumpWidget()
{
    delete ui;
}

void MemoryDumpWidget::on_pushButton_clicked()
{
    auto* edit = findChild<QLineEdit*>("lineEdit");
    const Word address = edit->text().toInt(0,8);

    emit OnDump(address);
}
