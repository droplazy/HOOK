/********************************************************************************
** Form generated from reading UI file 'display_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_WIDGET_H
#define UI_DISPLAY_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Display_Widget
{
public:
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *Display_Widget)
    {
        if (Display_Widget->objectName().isEmpty())
            Display_Widget->setObjectName("Display_Widget");
        Display_Widget->resize(700, 593);
        Display_Widget->setMinimumSize(QSize(700, 593));
        Display_Widget->setMaximumSize(QSize(700, 593));
        pushButton = new QPushButton(Display_Widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 560, 701, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 127);"));
        label = new QLabel(Display_Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 700, 560));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/pic/screen.png);"));
        label->setScaledContents(false);

        retranslateUi(Display_Widget);

        QMetaObject::connectSlotsByName(Display_Widget);
    } // setupUi

    void retranslateUi(QDialog *Display_Widget)
    {
        Display_Widget->setWindowTitle(QCoreApplication::translate("Display_Widget", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Display_Widget", "\345\201\234\346\255\242", nullptr));
        label->setText(QCoreApplication::translate("Display_Widget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Display_Widget: public Ui_Display_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_WIDGET_H
