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
    // 检查图片是否有效
    // 检查 QImage 是否有效
    if (img.isNull())
    {

        return ;
    }

   // qDebug() << "getted one flame !";

    // 检查图片大小
    if (img.width() > 5000 || img.height() > 5000) {
        qDebug() << "Image size is too large!";
        return;  // 图片尺寸过大
    }

    // 使用 QPixmap::fromImage() 转换图片，并检查转换是否成功
    QPixmap pixmap = QPixmap::fromImage(img);
    if (pixmap.isNull()) {
        qDebug() << "Failed to convert image to pixmap!";
        return;  // 转换失败，退出函数
    }

    // 调整大小并保持宽高比
    pixmap = pixmap.scaled(700, 560, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 设置调整大小后的pixmap到label
    ui->label->setPixmap(pixmap);
}
