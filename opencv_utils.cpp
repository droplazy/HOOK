#include "opencv_utils.h"
#include <QApplication>
#include <QScreen>
#include <QStandardPaths>
#include <QProcess>

#include <QTextStream>
#include <cmath>
#include <algorithm>
#include <ProDefine.h>


QStringList dreamWorldLocations = {
    "南瞻部洲", "东胜神洲", "西牛贺洲", "北俱芦洲",
    "长安城", "傲来国", "长寿村", "朱紫国",
    "凤巢", "龙窟", "地府迷宫", "海底迷宫",
    "凌霄宝殿", "战神山", "两界山",
    "大雁塔", "建邺城", "江南野外", "花果山", "女儿村",
    "龙窟入口", "女娲神迹", "方寸山", "天宫", "无底洞",
    "灵山雷音寺", "宝象国", "西梁女国", "大雪山", "金銮殿",
    "麒麟山", "碗子山", "东海湾", "无名鬼城"
};




// 计算 Levenshtein Distance（编辑距离）
int levenshteinDistance(const QString &str1, const QString &str2) {
    int len1 = str1.length();
    int len2 = str2.length();

    // 创建距离矩阵
    std::vector<std::vector<int>> dp(len1 + 1, std::vector<int>(len2 + 1));

    for (int i = 0; i <= len1; ++i) dp[i][0] = i;
    for (int j = 0; j <= len2; ++j) dp[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }
    return dp[len1][len2];
}

#include <QRegularExpression>

QString cleanOCRResult(const QString &input) {
    QRegularExpression reg("[^\u4e00-\u9fa5]");  // 匹配非汉字的字符
    QString result = input;  // 创建副本
    return result.replace(reg, "");  // 在副本上执行 replace
}


QString findMostSimilarLocation(const QString &input, const QStringList &locationList, int maxDistance = 3) {
    // 如果输入为空，直接返回“未知”
    if (input.isEmpty()) {
        return "未知";
    }

    // 清理 OCR 识别结果，去除字母等无关部分
    QString cleanedInput = cleanOCRResult(input);

    // 如果清理后的字符串为空，返回“未知”
    if (cleanedInput.isEmpty()) {
        return "未知";
    }

    QString closestLocation;
    int minDistance = std::numeric_limits<int>::max();

    for (const QString &location : locationList) {
        // 计算编辑距离（Levenshtein）
        int distance = levenshteinDistance(cleanedInput, location);

        // 记录最小距离
        if (distance < minDistance) {
            minDistance = distance;
            closestLocation = location;
        }
    }

    // 如果最小距离大于阈值，返回“未知”
    if (minDistance > maxDistance) {
        return "未知";
    }

    return closestLocation;
}


opencv_utils::opencv_utils()
{
    // ZeroPos.setX(0);
    // ZeroPos.setY(0);
}

// void opencv_utils::run()
// {
//     while(1)
//     {
//         if(startDispose)
//         {
//             disposeIMGformessage();
//             usleep(1000*1000);
//         }

//     }

// }

QImage opencv_utils::captureScreenQimage(const QRect &rect )
{
    // 获取主屏幕截图
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        qWarning() << "无法获取屏幕";
        //return cv::Mat();  // 返回一个空的cv::Mat
    }

    // 截取指定区域的截图
    QPixmap pixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());

    // 将 QPixmap 转换为 QImage
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        qWarning() << "截图转换为QImage失败";

    }
 return image;  // 返回一个空的
}


cv::Mat opencv_utils::captureScreenAndSave(const QRect &rect ,QString path)
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

    else if (path.isEmpty()||!image.save(path) ) {
        //qWarning() << "保存截图失败(或者不需要):" << path;
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

void opencv_utils::RectHignLight()
{

}

// void opencv_utils::GetCharacterPos()
// {

// }

QImage opencv_utils::FindPicTarget(cv::Mat targetImage, cv::Mat templateImage)
{
    // 检查图像是否为空
    if (targetImage.empty() || templateImage.empty()) {
        std::cerr << "无法加载图片" << std::endl;
        return QImage();  // 返回一个空的 QImage 对象
    }

    // 转换为灰度图
    cv::Mat targetGray, templateGray;
    cv::cvtColor(targetImage, targetGray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(templateImage, templateGray, cv::COLOR_BGR2GRAY);

    // 执行模板匹配
    cv::Mat result;
    cv::matchTemplate(targetGray, templateGray, result, cv::TM_CCOEFF_NORMED);

    // 找到最匹配的位置
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

    // 在目标图像上标记匹配区域
    cv::Rect matchRect(maxLoc.x, maxLoc.y, templateImage.cols, templateImage.rows);
    cv::rectangle(targetImage, matchRect, cv::Scalar(0, 255, 0), 2); // 用绿色框住匹配区域

    // 将 OpenCV 的 Mat 图像转换为 QImage
    // OpenCV 默认图像是 BGR 格式，这里将其转换为 RGB 格式
    QImage qImage(targetImage.data, targetImage.cols, targetImage.rows, targetImage.step, QImage::Format_RGB888);

    return qImage;  // 返回 QImage 对象
}


cv::Mat opencv_utils::captureScreenAndDisplay(const QRect &rect)
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

cv::Mat opencv_utils::capturePosition()
{
    QRect rect;
    cv::Mat ret;
    // rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,ZeroPos.y()+(130-90)*SCALE_FLOAT,90*SCALE_FLOAT,80*SCALE_FLOAT);
    rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,\
                                                           ZeroPos.y()+(130-90)*SCALE_FLOAT-15,\
     90*SCALE_FLOAT,80*SCALE_FLOAT);
   // ret = captureScreenAndDisplay(rect);
    ret = captureScreenAndSave(rect, "");    return ret;
}
cv::Mat opencv_utils::capturePositionForRect(QRect pos)
{
    QRect rect;
    cv::Mat ret;
    rect.setRect(ZeroPos.x()+pos.x(),ZeroPos.y()+pos.y(),pos.width(),pos.height());

    ret = captureScreenAndSave(rect, "");    return ret;
}

cv::Mat opencv_utils::captureGameWindow()
{
   // QRect rect;
    cv::Mat ret;
    // rect.setRect(ZeroPos.x()+(20-20)*SCALE_FLOAT,ZeroPos.y()+(130-90)*SCALE_FLOAT,90*SCALE_FLOAT,80*SCALE_FLOAT);

    QRect captureRect(ZeroPos.x(), ZeroPos.y(),EndPos.x()-ZeroPos.x(),EndPos.y()- ZeroPos.y());  // 设置需要截取的位置和宽高

    // 90*SCALE_FLOAT,80*SCALE_FLOAT);
    ret = captureScreenAndSave(captureRect, "");    return ret;
}
// QImage image3("E:/qtpro/ScreenCapture/测试/4.png");

// // 检查图片是否加载成功
// if (image3.isNull()) {
//     qDebug() << "图片加载失败!";
// } else {
//     qDebug() << "图片加载成功!";
// }

// 将 QImage 转换为 cv::Mat
void opencv_utils::disposeIMGformessage()
{
    qDebug() << "ZeroPos: (" << ZeroPos.x() << "," << ZeroPos.y() << ")";
    qDebug() << "EndPos: (" << EndPos.x() << "," << EndPos.y() << ")";

   // cv::Mat targetImg = captureGameWindow();
  //  cv::Mat templateImg =capturePosition();

    qDebug() << "****************************************************";
    QRect rect(+53,+207,138,20);
    cv::Mat posText = capturePositionForRect(rect);
    QString position=recognizeTextFromMat(posText,OCR_ENGLISH);

    rect.setRect(+45,+120,115,30);
    posText = capturePositionForRect(rect);
    QString location =   recognizeTextFromMat(posText,OCR_CHINESE_SIMPLE);
    QString result = findMostSimilarLocation(location, dreamWorldLocations);

    qDebug()<< "最相似的地名是: " << result << "OCR:"<<position;
    qDebug() << "****************************************************";
}

QString opencv_utils::recognizeTextFromMat(const cv::Mat &inputMat ,QString language) {
    // 将 cv::Mat 转换为灰度图
    cv::Mat grayMat;
    cv::cvtColor(inputMat, grayMat, cv::COLOR_BGR2GRAY);

    // 使用 Otsu 二值化方法进行二值化处理，自动选择最佳阈值
    cv::Mat binaryMat;
    cv::threshold(grayMat, binaryMat, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // 反转二值化图像（黑白反转）
    cv::Mat invertedMat;
    cv::bitwise_not(binaryMat, invertedMat);

    // 保存反转后的二值化图像
    QString tempInvertedImagePath = "C:/Users/KANDAGAWA/Desktop/temp_inverted_image.png";
    cv::imwrite(tempInvertedImagePath.toStdString(), invertedMat);

    // 设置 Tesseract 执行路径和输出文件路径
    QString tesseractPath = "C:/Program Files/Tesseract-OCR/tesseract.exe";
    QString outputPath = "C:/Users/KANDAGAWA/Desktop/output";
    //QString language = "eng";

    // 创建 QProcess 调用 Tesseract 命令
    QProcess process;
    QStringList arguments;
    arguments << tempInvertedImagePath << outputPath << "-l" << language << "--dpi" << "300" << "--psm" << "6";

    // 启动进程并等待 Tesseract 处理
    process.start(tesseractPath, arguments);
    process.waitForFinished();

    // 读取 Tesseract 输出的文本
    QFile outputFile(outputPath + ".txt");
    if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&outputFile);
        QString recognizedText = in.readAll();
        outputFile.close();

        // 输出识别的文字
        qDebug() << "识别的文字： " << recognizedText;
        return recognizedText;
    } else {
        qDebug() << "无法读取 Tesseract 输出文件!";
        return "";
    }


}


