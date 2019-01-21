#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Common/Types.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void setPcRequest(const Word value);
    void stepRequest();
    void runRequest();
    void stopRequest();

private slots:
    void on_setPcButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
