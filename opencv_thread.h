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


using namespace cv;
using namespace std;


#define SCALE_FLOAT 2.2f



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
public slots:
    void testSLot();
signals:
    void getPic(QImage);
};


class FeatureMatcher {
public:
    static cv::Mat matchTemplateAndShow(const cv::Mat &targetImg, const cv::Mat &templateImg) {
        // 转换为灰度图像
        cv::Mat grayTarget, grayTemplate;
        cv::cvtColor(targetImg, grayTarget, cv::COLOR_BGR2GRAY);
        cv::cvtColor(templateImg, grayTemplate, cv::COLOR_BGR2GRAY);

        // 初始化ORB特征点检测器
        cv::Ptr<cv::ORB> orb = cv::ORB::create();

        // 检测特征点和计算描述符
        std::vector<cv::KeyPoint> keypointsTarget, keypointsTemplate;
        cv::Mat descriptorsTarget, descriptorsTemplate;
        orb->detectAndCompute(grayTarget, cv::noArray(), keypointsTarget, descriptorsTarget);
        orb->detectAndCompute(grayTemplate, cv::noArray(), keypointsTemplate, descriptorsTemplate);

        // 使用暴力匹配器进行匹配
        cv::BFMatcher matcher(cv::NORM_HAMMING, true); // 使用汉明距离和交叉验证
        std::vector<cv::DMatch> matches;
        matcher.match(descriptorsTarget, descriptorsTemplate, matches);

        // 计算最小匹配距离
        double minDist = 100.0;
        for (int i = 0; i < descriptorsTarget.rows; i++) {
            double dist = matches[i].distance;
            if (dist < minDist) {
                minDist = dist;
            }
        }

        // 只保留匹配距离最小的点
        std::vector<cv::DMatch> goodMatches;
        for (int i = 0; i < descriptorsTarget.rows; i++) {
            if (matches[i].distance <= minDist * 1.5) {  // 适当放宽距离范围
                goodMatches.push_back(matches[i]);
            }
        }

        // 绘制最优匹配结果
        cv::Mat imgMatches;
        cv::drawMatches(targetImg, keypointsTarget, templateImg, keypointsTemplate, goodMatches, imgMatches);

        return imgMatches;  // 返回绘制好的匹配图
    }
};


#endif // OPENCV_THREAD_H
