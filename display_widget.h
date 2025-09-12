#ifndef DISPLAY_WIDGET_H
#define DISPLAY_WIDGET_H

#include <QDialog>

namespace Ui {
class Display_Widget;
}

class Display_Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Display_Widget(QWidget *parent = nullptr);
    ~Display_Widget();
signals:
    void closeSig();
private slots:
    void on_pushButton_clicked();
    void displayInstace(QImage img);
private:
    Ui::Display_Widget *ui;
};

#endif // DISPLAY_WIDGET_H
