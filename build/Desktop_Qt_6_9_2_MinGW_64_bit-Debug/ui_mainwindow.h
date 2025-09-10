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
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 700);
        MainWindow->setMinimumSize(QSize(800, 700));
        MainWindow->setMaximumSize(QSize(800, 700));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_gameinfo = new QLabel(centralwidget);
        label_gameinfo->setObjectName("label_gameinfo");
        label_gameinfo->setGeometry(QRect(20, 90, 700, 560));
        label_gameinfo->setMinimumSize(QSize(700, 560));
        label_gameinfo->setMaximumSize(QSize(700, 560));
        label_gameinfo->setStyleSheet(QString::fromUtf8("background-image: url(:/pic/3.png);"));
        label_gameinfo->setScaledContents(true);
        pushButton_capture = new QPushButton(centralwidget);
        pushButton_capture->setObjectName("pushButton_capture");
        pushButton_capture->setGeometry(QRect(21, 11, 80, 24));
        pushButton_capture->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(156, 156, 156);"));
        label_sysinfor = new QLabel(centralwidget);
        label_sysinfor->setObjectName("label_sysinfor");
        label_sysinfor->setGeometry(QRect(20, 50, 701, 31));
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
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 130, 91, 71));
        label->setStyleSheet(QString::fromUtf8("border: 3px solid red;background: transparent;"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(540, 130, 178, 35));
        label_2->setStyleSheet(QString::fromUtf8("border: 3px solid red;background: transparent;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 220, 421, 251));
        label_3->setStyleSheet(QString::fromUtf8("border: 3px solid red;background: transparent;"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(410, 620, 311, 31));
        label_4->setStyleSheet(QString::fromUtf8("border: 3px solid red;background: transparent;"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 550, 311, 101));
        label_5->setStyleSheet(QString::fromUtf8("border: 3px solid red;background: transparent;"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(580, 210, 141, 231));
        label_6->setStyleSheet(QString::fromUtf8("border: 3px solid red;background: transparent;"));
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
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
