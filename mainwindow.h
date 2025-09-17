#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QDir>
#include <QDateTime>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <httpclient.h>
#include <QKeyEvent>
#include <QCoreApplication>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class event_pthread;

class Display_Widget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void  GetORCRegnizeToNetwork(QString picBase64);
signals:
    void DebugPress(void);

public slots:
    void updateWindowInfo();
    void GetNeedRegnizePic(QString picBase64);
private slots:
    void on_pushButton_capture_clicked();
    void on_pushButton_imgtest_clicked();
    void on_pushButton_capture_2_clicked();
    void on_pushButton_START_clicked();
    void ChindWidegtClosed();
    void MoveMouserToTarget();
protected:
        void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_F12) {
            // 按下 F12 时退出应用
            QCoreApplication::quit();
        }
        QMainWindow::keyPressEvent(event);  // 继续处理其他按键事件
    }
private:
    Ui::MainWindow *ui;
     HttpClient *p_http;
    event_pthread *p_thread;
    Display_Widget *w_displayTest;

};
#endif // MAINWINDOW_H
