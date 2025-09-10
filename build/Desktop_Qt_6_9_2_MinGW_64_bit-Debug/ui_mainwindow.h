/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
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
    QLabel *label_gameinfo;
    QPushButton *pushButton_capture;
    QLabel *label_sysinfor;
    QPushButton *pushButton_imgtest;
    QPushButton *pushButton_capture_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_gameinfo = new QLabel(centralwidget);
        label_gameinfo->setObjectName("label_gameinfo");
        label_gameinfo->setGeometry(QRect(20, 90, 751, 461));
        label_gameinfo->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        pushButton_capture = new QPushButton(centralwidget);
        pushButton_capture->setObjectName("pushButton_capture");
        pushButton_capture->setGeometry(QRect(21, 11, 80, 24));
        pushButton_capture->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(156, 156, 156);"));
        label_sysinfor = new QLabel(centralwidget);
        label_sysinfor->setObjectName("label_sysinfor");
        label_sysinfor->setGeometry(QRect(20, 50, 751, 31));
        label_sysinfor->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(170, 0, 0);"));
        pushButton_imgtest = new QPushButton(centralwidget);
        pushButton_imgtest->setObjectName("pushButton_imgtest");
        pushButton_imgtest->setGeometry(QRect(200, 10, 80, 24));
        pushButton_imgtest->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(156, 156, 156);"));
        pushButton_capture_2 = new QPushButton(centralwidget);
        pushButton_capture_2->setObjectName("pushButton_capture_2");
        pushButton_capture_2->setGeometry(QRect(110, 10, 80, 24));
        pushButton_capture_2->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(156, 156, 156);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_gameinfo->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_capture->setText(QCoreApplication::translate("MainWindow", "\347\252\227\345\217\243\350\216\267\345\217\226", nullptr));
        label_sysinfor->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_imgtest->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\346\265\213\350\257\225", nullptr));
        pushButton_capture_2->setText(QCoreApplication::translate("MainWindow", "\346\210\221\350\216\267\345\217\226\344\272\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
