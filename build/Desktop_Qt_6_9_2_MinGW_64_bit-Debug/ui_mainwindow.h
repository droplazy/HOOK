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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_capture;
    QLabel *label_sysinfor;
    QPushButton *pushButton_imgtest;
    QPushButton *pushButton_START;
    QPushButton *pushButton_START_2;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(497, 449);
        MainWindow->setMinimumSize(QSize(497, 449));
        MainWindow->setMaximumSize(QSize(497, 449));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton_capture = new QPushButton(centralwidget);
        pushButton_capture->setObjectName("pushButton_capture");
        pushButton_capture->setGeometry(QRect(21, 11, 80, 24));
        pushButton_capture->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(156, 156, 156);"));
        label_sysinfor = new QLabel(centralwidget);
        label_sysinfor->setObjectName("label_sysinfor");
        label_sysinfor->setGeometry(QRect(20, 50, 441, 31));
        label_sysinfor->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_imgtest = new QPushButton(centralwidget);
        pushButton_imgtest->setObjectName("pushButton_imgtest");
        pushButton_imgtest->setGeometry(QRect(110, 10, 80, 24));
        pushButton_imgtest->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(156, 156, 156);"));
        pushButton_START = new QPushButton(centralwidget);
        pushButton_START->setObjectName("pushButton_START");
        pushButton_START->setGeometry(QRect(200, 10, 80, 24));
        pushButton_START->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 1, 1);"));
        pushButton_START_2 = new QPushButton(centralwidget);
        pushButton_START_2->setObjectName("pushButton_START_2");
        pushButton_START_2->setGeometry(QRect(290, 10, 80, 24));
        pushButton_START_2->setStyleSheet(QString::fromUtf8("background-color: rgb(1, 1, 1);"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(20, 80, 461, 331));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 497, 21));
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
        pushButton_capture->setText(QCoreApplication::translate("MainWindow", "\347\252\227\345\217\243\350\216\267\345\217\226", nullptr));
        label_sysinfor->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_imgtest->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213/\345\201\234\346\255\242\346\265\201", nullptr));
        pushButton_START->setText(QCoreApplication::translate("MainWindow", "KAISHI", nullptr));
        pushButton_START_2->setText(QCoreApplication::translate("MainWindow", "KAISHI", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\202\271\345\207\273</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
