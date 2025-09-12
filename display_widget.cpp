#include "display_widget.h"
#include "ui_display_widget.h"

Display_Widget::Display_Widget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Display_Widget)
{
    ui->setupUi(this);
}

Display_Widget::~Display_Widget()
{
    delete ui;
}

void Display_Widget::on_pushButton_clicked()
{
    emit closeSig();
    delete this; // De
}

void Display_Widget::displayInstace(QImage img)
{
    // 将选定的图片调整为 700x560 像素，并放入label
    QPixmap pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(700, 560, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 调整为 700x560，并保持宽高比

    ui->label->setPixmap(pixmap); // 设置调整大小后的pixmap到label
}
