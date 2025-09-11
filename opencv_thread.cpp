#include "opencv_thread.h"
#include <QApplication>
#include <QScreen>
#include <QStandardPaths>
opencv_thread::opencv_thread()
{
    ZeroPos.setX(0);
    ZeroPos.setY(0);
}
 // 将QImage转换为cv::Mat
    cv::Mat QImageToCvMat(const QImage &image) {
        if (image.format() == QImage::Format_RGB888) {
            return cv::Mat(image.height(), image.width(), CV_8UC3, const_cast<uchar*>(image.bits()), image.bytesPerLine()).clone();
        } else if (image.format() == QImage::Format_Grayscale8) {
            return cv::Mat(image.height(), image.width(), CV_8UC1, const_cast<uchar*>(image.bits()), image.bytesPerLine()).clone();
        }
        return cv::Mat();  // 不支持的格式
    }

    // 将cv::Mat转换为QImage
    QImage cvMatToQImage(const cv::Mat &mat) {
        if (mat.empty()) return QImage();

        if (mat.type() == CV_8UC3) {
            return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
        } else if (mat.type() == CV_8UC1) {
            return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
        }
        return QImage();
    }
void opencv_thread::run()
{
    while(1)
    {
        if(0)
        {
            disposeIMGformessage();
        }
        usleep(200*1000);
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

    if (!image.save(path)) {
        qWarning() << "保存截图失败:" << path;
    } else {
        qDebug() << "截图已保存到:" << path;
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

cv::Mat QImage2cvMat(const QImage &image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_Grayscale8: // 灰度图，每个像素点1个字节（8位）
        // Mat构造：行数，列数，存储结构，数据，step每行多少字节
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_ARGB32: // uint32存储0xAARRGGBB，pc一般小端存储低位在前，所以字节顺序就成了BGRA
    case QImage::Format_RGB32: // Alpha为FF
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888: // RR,GG,BB字节顺序存储
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        // opencv需要转为BGR的字节顺序
        cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
        break;
    case QImage::Format_RGBA64: // uint64存储，顺序和Format_ARGB32相反，RGBA
        mat = cv::Mat(image.height(), image.width(), CV_16UC4, (void*)image.constBits(), image.bytesPerLine());
        // opencv需要转为BGRA的字节顺序
        cv::cvtColor(mat, mat, cv::COLOR_RGBA2BGRA);
        break;
    }
    return mat;
}
void opencv_thread::disposeIMGformessage()
{
    qDebug() << "ZeroPos: (" << ZeroPos.x() << "," << ZeroPos.y() << ")";
    qDebug() << "EndPos: (" << EndPos.x() << "," << EndPos.y() << ")";

    cv::Mat targetImg = captureGameWindow();
    // QImage image3("E:/qtpro/ScreenCapture/测试/4.png");

    // // 检查图片是否加载成功
    // if (image3.isNull()) {
    //     qDebug() << "图片加载失败!";
    // } else {
    //     qDebug() << "图片加载成功!";
    // }

    // 将 QImage 转换为 cv::Mat
    cv::Mat templateImg =capturePosition();

    // 调用特征匹配
    FeatureMatchingW(targetImg, templateImg);
}


void opencv_thread::FeatureMatchingW(cv::Mat targetImg,cv::Mat templateImg)
{
    // // 将QImage转换为cv::Mat
    // cv::Mat targetImg = QImageToCvMat(image1);
    // cv::Mat templateImg = QImageToCvMat(image2);

    if (targetImg.empty()) {
        std::cerr << "Error: Could not load targetImg." << std::endl;

        return;
    }
    else if(templateImg.empty())
    {
        std::cerr << "Error: Could not load templateImg." << std::endl;
        return;
    }

    // 调用接口进行匹配
    cv::Mat imgMatches = FeatureMatcher::matchTemplateAndShow(targetImg, templateImg);

    // 将匹配结果转为 QImage 以便显示
    QImage qImgMatches = QImage(imgMatches.data, imgMatches.cols, imgMatches.rows, imgMatches.step, QImage::Format_BGR888);
    if (!qImgMatches.save("E:/qtpro/ScreenCapture/测试/3.png")) {
        qWarning() << "保存截图失败:" << "E:/qtpro/ScreenCapture/测试/3.png";
    } else {
        qDebug() << "截图已保存到:" << "E:/qtpro/ScreenCapture/测试/3.png";
    }

     emit getPic(qImgMatches);  // 如果需要，发射信号传输QImage

}
void opencv_thread::testSLot()
{
    qDebug()<< "123321";
    disposeIMGformessage();
}
