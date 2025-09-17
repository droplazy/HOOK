#ifndef opencv_utils_H
#define opencv_utils_H

// #include <QObject>
// #include <QThread>
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




class opencv_utils {
public:
    opencv_utils();

    static cv::Mat captureScreenAndDisplay(const QRect &rect);

    static void disposeIMGformessage();

   // bool startDispose = false;
    static void FeatureMatchingW(cv::Mat targetImg, cv::Mat templateImg);

    static cv::Mat capturePosition();
    static cv::Mat captureGameWindow();
    static cv::Mat captureScreenAndSave(const QRect &rect, QString path);

    static void RectHignLight();
    static void GetCharacterPos(cv::Mat targetImage,cv::Mat templateImage);
    static QImage FindPicTarget(cv::Mat targetImage,cv::Mat templateImage);
    static cv::Mat capturePositionForRect(QRect pos);
    static QString recognizeTextFromMat(const cv::Mat &inputMat, QString language);
    static QImage captureScreenQimage(const QRect &rect);
};
using namespace cv;

class ImageWindow : public QWidget
{
public:
    ImageWindow(const QImage &image) : img(image) {}

protected:
    void paintEvent(QPaintEvent *event) override {
        Q_UNUSED(event);  // 标记未使用的参数
        QPainter painter(this);
        painter.drawImage(0, 0, img);
    }

public:
    QImage img;
};


#endif // opencv_utils_H
