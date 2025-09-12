#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>
#include <QVBoxLayout>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class opencv_thread;
class Display_Widget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void DebugPress(void);

public slots:
    void updateWindowInfo();
private slots:

    void on_pushButton_capture_clicked();

    void on_pushButton_imgtest_clicked();

    void on_pushButton_capture_2_clicked();
    void on_pushButton_START_clicked();
    void ChindWidegtClosed();
protected:
    //void paintEvent(QPaintEvent *event) override;
private:
    Ui::MainWindow *ui;
    bool streamOn = false;
    opencv_thread *p_opencv;
    Display_Widget *w_displayTest;
};
#endif // MAINWINDOW_H
