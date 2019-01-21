#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setPcButton_clicked()
{
    QLineEdit* e = findChild<QLineEdit*>("pcEdit");

    bool ok = false;
    Word value = static_cast<Word>(e->text().toInt(&ok, 8));

    emit setPcRequest(value);
    qDebug() << QString("emit setPcRequest(%1)\n").arg(value);
}
