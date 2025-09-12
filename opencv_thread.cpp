#include "opencv_thread.h"
#include <QApplication>
#include <QScreen>
#include <QStandardPaths>
opencv_thread::opencv_thread()
{
    ZeroPos.setX(0);
    ZeroPos.setY(0);
}

void opencv_thread::run()
{
    while(1)
    {
        if(startDispose)
        {
            disposeIMGformessage();
        }

    }

}
cv::Mat opencv_thread::captureScreenAndSave(const QRect &rect ,QString path)
{
    // 获取主屏幕截图
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        qWarning() << "无法获取屏幕";
        return cv::Mat();  // 返回一个空的cv::Mat
    }

    // 截取指定区域的截图
    QPixmap pixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());

    // 将 QPixmap 转换为 QImage
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        qWarning() << "截图转换为QImage失败";
        return cv::Mat();  // 返回一个空的cv::Mat
    }

    // // 将 QImage 保存到桌面
    // QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    // QString filePath = desktopPath + "/1.png";
    // static bool
    // if (!image.save(path)) {
    //     qWarning() << "保存截图失败:" << path;
    // } else {
    //     qDebug() << "截图已保存到:" << path;
    // }
    if(startDispose)
    {
        emit getPic(image);
    }
    // 将 QImage 转换为 cv::Mat
    cv::Mat mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
    if (mat.empty()) {
        qWarning() << "OpenCV Mat 转换失败";
        return cv::Mat();  // 返回一个空的cv::Mat
    }

    // 将 Mat 转换为 BGR（如果需要进一步处理）
    cv::Mat matBGR;
    cv::cvtColor(mat, matBGR, cv::COLOR_BGRA2BGR);

    // 返回转换后的 BGR 图像
    return matBGR;
}

void opencv_thread::FindPicTarget()
{
    // 读取目标图像和模板图像
    Mat targetImage = imread("C:/Users/KANDAGAWA/Pictures/zm/2.png", IMREAD_COLOR);
    Mat templateImage = imread("C:/Users/KANDAGAWA/Pictures/zm/1.png", IMREAD_COLOR);

    if (targetImage.empty() || templateImage.empty()) {
        std::cerr << "无法加载图片" << std::endl;
        return ;
    }

    // 转换为灰度图
    Mat targetGray, templateGray;
    cvtColor(targetImage, targetGray, COLOR_BGR2GRAY);
    cvtColor(templateImage, templateGray, COLOR_BGR2GRAY);

    // 执行模板匹配
    Mat result;
    matchTemplate(targetGray, templateGray, result, TM_CCOEFF_NORMED);

    // 找到最匹配的位置
    double minVal, maxVal;
    Point minLoc, maxLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    // 在目标图像上标记匹配区域
    Rect matchRect(maxLoc.x, maxLoc.y, templateImage.cols, templateImage.rows);
    rectangle(targetImage, matchRect, Scalar(0, 255, 0), 2); // 用绿色框住匹配区域

    // 显示结果
    QImage qImage(targetImage.data, targetImage.cols, targetImage.rows, targetImage.step, QImage::Format_BGR888);
    ImageWindow window(qImage);
}

cv::Mat opencv_thread::captureScreenAndDisplay(const QRect &rect)
{
    // 获取主屏幕截图
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        qWarning() << "无法获取屏幕";
        return cv::Mat();  // 返回一个空的cv::Mat
    }

    // 截取指定区域的截图
    QPixmap pixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());

    // 将 QPixmap 转换为 QImage
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        qWarning() << "截图转换为QImage失败";
        return cv::Mat();  // 返回一个空的cv::Mat
    }

   // emit getPic(image);  // 如果需要，发射信号传输QImage

    // 将 QImage 转换为 cv::Mat
    cv::Mat mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
    if (mat.empty()) {
        qWarning() << "OpenCV Mat 转换失败";
        return cv::Mat();  // 返回一个空的cv::Mat
    }

    // 将 Mat 转换为 BGR（如果需要进一步处理）
    cv::Mat matBGR;
    cv::cvtColor(mat, matBGR, cv::COLOR_BGRA2BGR);

    // 返回转换后的 BGR 图像
    return matBGR;
}

cv::Mat opencv_thread::capturePosition()
{
    QRect rect;
    cv::Mat ret;
    // rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,ZeroPos.y()+(130-90)*SCALE_FLOAT,90*SCALE_FLOAT,80*SCALE_FLOAT);
    rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,\
                                                           ZeroPos.y()+(130-90)*SCALE_FLOAT-15,\
     90*SCALE_FLOAT,80*SCALE_FLOAT);
   // ret = captureScreenAndDisplay(rect);
    ret = captureScreenAndSave(rect, "E:/qtpro/ScreenCapture/测试/1.png");    return ret;
}
cv::Mat opencv_thread::captureGameWindow()
{
   // QRect rect;
    cv::Mat ret;
    // rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,ZeroPos.y()+(130-90)*SCALE_FLOAT,90*SCALE_FLOAT,80*SCALE_FLOAT);

    QRect captureRect(ZeroPos.x(), ZeroPos.y(),EndPos.x()-ZeroPos.x(),EndPos.y()- ZeroPos.y());  // 设置需要截取的位置和宽高

    // 90*SCALE_FLOAT,80*SCALE_FLOAT);
ret = captureScreenAndSave(captureRect, "E:/qtpro/ScreenCapture/测试/2.png");    return ret;
}
// QImage image3("E:/qtpro/ScreenCapture/测试/4.png");

// // 检查图片是否加载成功
// if (image3.isNull()) {
//     qDebug() << "图片加载失败!";
// } else {
//     qDebug() << "图片加载成功!";
// }

// 将 QImage 转换为 cv::Mat
void opencv_thread::disposeIMGformessage()
{
    qDebug() << "ZeroPos: (" << ZeroPos.x() << "," << ZeroPos.y() << ")";
    qDebug() << "EndPos: (" << EndPos.x() << "," << EndPos.y() << ")";

    cv::Mat targetImg = captureGameWindow();
    //cv::Mat templateImg =capturePosition();
}


void opencv_thread::testSLot()
{
    qDebug()<< "123321";
    disposeIMGformessage();
}
