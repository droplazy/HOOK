#ifndef OPENCV_THREAD_H
#define OPENCV_THREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QImage>
#include <QPixmap>
#include <QScreen>
#include <QGuiApplication>
#include <QWidget>
#include <QDateTime>
#include <QDir>
#include <QPainter>

using namespace cv;
using namespace std;


#define SCALE_FLOAT 2.2f
#define OCR_CHINESE_SIMPLE "chi_sim"
#define OCR_ENGLISH "eng"



class opencv_thread: public QThread
{
    Q_OBJECT
public:

    opencv_thread();
    virtual void run();
    Mat captureScreenAndDisplay(const QRect &rect);

    QPoint ZeroPos;
    QPoint EndPos;
    void disposeIMGformessage();

    bool startDispose=false;
    void FeatureMatchingW(cv::Mat targetImg,cv::Mat templateImg);

    cv::Mat capturePosition();
    cv::Mat captureGameWindow();
    cv::Mat captureScreenAndSave(const QRect &rect, QString path);


    void RectHignLight();
    void GetCharacterPos();
    void FindPicTarget();
    cv::Mat capturePositionForRect(QRect pos);
    QString recognizeTextFromMat(const cv::Mat &inputMat ,QString language);
public slots:
    void testSLot();
signals:
    void getPic(QImage);
};

using namespace cv;

class ImageWindow : public QWidget
{
public:
    ImageWindow(const QImage &image) : img(image) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.drawImage(0, 0, img);
    }

public:
    QImage img;
};


#endif // OPENCV_THREAD_H
