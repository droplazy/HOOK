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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage captureWindow(int x, int y, int width, int height);
    void saveImage(const QImage &image);
    QImage captureScreen(int x, int y, int width, int height);
    void GetImage();
    void captureScreenAndSave(const QRect &rect);
    void ImageStream();
    void captureScreenAndDisplay(const QRect &rect);
    void LayoutAlign();
    void debugPicture();
public slots:
    void updateWindowInfo();
    void showPostionlabel(QImage img );
private slots:

    void on_pushButton_capture_clicked();

    void on_pushButton_imgtest_clicked();

    void on_pushButton_capture_2_clicked();
    void on_pushButton_START_clicked();

protected:
    //void paintEvent(QPaintEvent *event) override;
private:
    Ui::MainWindow *ui;
    bool streamOn = false;
    opencv_thread *p_opencv;
   // QTimer
};
#endif // MAINWINDOW_H
