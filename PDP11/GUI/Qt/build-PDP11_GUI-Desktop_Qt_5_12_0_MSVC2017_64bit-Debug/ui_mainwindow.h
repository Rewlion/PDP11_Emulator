/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *display;
    QPushButton *setPcButton;
    QPushButton *stepButton;
    QPushButton *runButton;
    QPushButton *stopButton;
    QLineEdit *pcEdit;
    QListView *memoryView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        display = new QLabel(centralwidget);
        display->setObjectName(QString::fromUtf8("display"));
        display->setGeometry(QRect(0, 0, 500, 500));
        setPcButton = new QPushButton(centralwidget);
        setPcButton->setObjectName(QString::fromUtf8("setPcButton"));
        setPcButton->setGeometry(QRect(410, 500, 91, 31));
        stepButton = new QPushButton(centralwidget);
        stepButton->setObjectName(QString::fromUtf8("stepButton"));
        stepButton->setGeometry(QRect(0, 530, 91, 31));
        runButton = new QPushButton(centralwidget);
        runButton->setObjectName(QString::fromUtf8("runButton"));
        runButton->setGeometry(QRect(0, 560, 91, 31));
        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setGeometry(QRect(0, 590, 91, 31));
        pcEdit = new QLineEdit(centralwidget);
        pcEdit->setObjectName(QString::fromUtf8("pcEdit"));
        pcEdit->setGeometry(QRect(0, 500, 411, 31));
        memoryView = new QListView(centralwidget);
        memoryView->setObjectName(QString::fromUtf8("memoryView"));
        memoryView->setGeometry(QRect(90, 530, 321, 171));
        memoryView->setViewMode(QListView::ListMode);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        display->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        setPcButton->setText(QApplication::translate("MainWindow", "SetPC", nullptr));
        stepButton->setText(QApplication::translate("MainWindow", "Step", nullptr));
        runButton->setText(QApplication::translate("MainWindow", "Run", nullptr));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
