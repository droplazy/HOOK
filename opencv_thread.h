#ifndef OPENCV_THREAD_H
#define OPENCV_THREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <QImage>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QWidget>
#include <QDateTime>
#include <QDir>


using namespace cv;
using namespace std;


#define SCALE_FLOAT (1040.0f / 700.0f)



class opencv_thread: public QThread
{
    Q_OBJECT
public:

    opencv_thread();
    virtual void run();
    void captureScreenAndDisplay(const QRect &rect);

    QPoint ZeroPos;
    void disposeIMGformessage();

    bool startDispose=false;
signals:
    void getPic(QImage);
};

#endif // OPENCV_THREAD_H
