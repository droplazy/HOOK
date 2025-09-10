#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QDir>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

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
public slots:
    void updateWindowInfo();
private slots:

    void on_pushButton_capture_clicked();

private:
    Ui::MainWindow *ui;

   // QTimer
};
#endif // MAINWINDOW_H
