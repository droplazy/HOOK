#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QPoint>
#include <QScreen>
#include <windows.h>
#include <QDebug>
#include <vector>
#include "mainwindow.h"
#include <QPixmap>
#include <opencv2/opencv.hpp>



QPoint mousePos(0, 0);;
QPoint startPos(0, 0);;
QPoint endPos(0, 0);;
bool isCpature = false;
// 鼠标钩子
HHOOK mouseHook;
std::vector<QPoint> clickPositions; // 存储点击位置
bool appExit = false; // 控制程序退出

// 鼠标事件回调函数
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT* hookStruct = (MSLLHOOKSTRUCT*)lParam;

        switch (wParam) {
        case WM_MOUSEMOVE: {
            // 获取当前鼠标位置
            POINT pt = hookStruct->pt;
            //qDebug() << "Mouse moved to: " << QPoint(pt.x, pt.y);
            mousePos= QPoint(pt.x, pt.y);
            break;
        }
        case WM_LBUTTONDOWN: {
            // 记录点击位置
            POINT pt = hookStruct->pt;
            QPoint clickPos(pt.x, pt.y);
            clickPositions.push_back(clickPos);
            //qDebug() << "Left mouse button pressed at:" << clickPos;
            if(isCpature)
            {
                startPos=clickPos;
            }
            // 重绘透明窗口
            if (QWidget* topWindow = QApplication::topLevelWidgets().isEmpty() ? nullptr : QApplication::topLevelWidgets().first()) {
                topWindow->update(); // 触发重绘
            }
            break;
        }
        case WM_LBUTTONUP: {
            POINT pt = hookStruct->pt;
            QPoint releasePos(pt.x, pt.y);
            if(isCpature)
            {
                endPos=releasePos;
                isCpature =false;;
            }
            //qDebug() << "Left mouse button released at:" << releasePos;
            break;
        }
        }
    }

    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
QString getTimestamp()
{
    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    return QString::number(timestamp);
}

// 安装鼠标钩子
void installMouseHook()
{
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
}

// 移除鼠标钩子
void removeMouseHook()
{
    UnhookWindowsHookEx(mouseHook);
}

// 自动移动鼠标并进行点击
void moveMouseAndClick(int x, int y) {
    // 设置鼠标位置
    SetCursorPos(x, y);

    // 模拟鼠标按下事件
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);

    // 模拟鼠标抬起事件
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);

    qDebug() << "Mouse moved and clicked at:" << QPoint(x, y);
}

void MainWindow::updateWindowInfo()
{



      QString info = QString("Mouse Position: %1 x %2").arg(mousePos.x()).arg(mousePos.y())+\
                   "    "+QString("start Position: %1 x %2").arg(startPos.x()).arg(startPos.y())+\
                   "    "+QString("end Position: %1 x %2").arg(endPos.x()).arg(endPos.y());


    qDebug() <<info;
    ui->label_sysinfor->setText(info);  // 显示在QLabel中

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWindowInfo);
    timer->start(1); // 每秒更新一次
    installMouseHook();  // 安装鼠标钩子

    // 启动定时器，10秒后退出程序
    //  QTimer::singleShot(10000, this, &TransparentWindow::closeApp);

    // 自动将鼠标移到指定位置 (例如：屏幕中心)
    moveMouseAndClick(422, 453);  // 可以根据需要修改目标位置
}

MainWindow::~MainWindow()
{
    removeMouseHook();  // 移除钩子

    delete ui;
}



void MainWindow::on_pushButton_capture_clicked()
{

    static bool isAcitive = false;
    isAcitive = !isAcitive;
    // 切换按钮状态
    if (isAcitive) {
        isCpature = true;
        ui->pushButton_capture->setStyleSheet("background-color: rgb(255, 1, 1);");
    } else {

        ui->pushButton_capture->setStyleSheet("background-color: rgb(255, 255, 255);");
        GetImage();
    }
    qDebug("debug");
}


QImage MainWindow::captureScreen(int x, int y, int width, int height)
{
    // 获取屏幕
    QScreen *screen = QGuiApplication::primaryScreen();

    if (!screen)
        return QImage();

    // 获取当前屏幕的 DPI 缩放因子
    qreal dpiScalingFactor = screen->devicePixelRatio();

    // 创建 QRect，并将坐标和尺寸（考虑 DPI）调整为实际物理像素
    QRect rect(x, y, width, height);

    // 计算缩放后的宽度和高度
    int scaledWidth = static_cast<int>(rect.width() * dpiScalingFactor);
    int scaledHeight = static_cast<int>(rect.height() * dpiScalingFactor);

    // 创建一个新的 QRect，使用缩放后的尺寸
    QRect scaledRect(rect.x(), rect.y(), scaledWidth, scaledHeight);

    // 截图，使用缩放后的区域
    QPixmap screenshot = screen->grabWindow(0, scaledRect.x(), scaledRect.y(),
                                            scaledRect.width(), scaledRect.height());

    // 将 QPixmap 转换为 QImage
    return screenshot.toImage();
}




// 获取某个窗口的图像并保存到 QImage（假设你已经知道窗口的 x, y, width, height）
QImage MainWindow::captureWindow(int x, int y, int width, int height)
{
    // 获取窗口的图像，这里使用一个屏幕区域作为例子
    return captureScreen(x, y, width, height);
}
void MainWindow::saveImage(const QImage &image)
{
    // 获取当前时间戳
    QString timestamp = getTimestamp();

    // 指定保存路径
    QString savePath = "E:/qtpro/ScreenCapture/测试/" + timestamp + ".png";

    // 确保目录存在
    QDir dir;
    if (!dir.exists("E:/qtpro/ScreenCapture/测试")) {
        dir.mkpath("E:/qtpro/ScreenCapture/测试");
    }

    // 保存图像到指定路径
    image.save(savePath);
    //  qDebug() << "Image saved to: " << savePath;
}
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>

void MainWindow::captureScreenAndSave(const QRect &rect)
{
    // 获取主屏幕截图
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        qWarning() << "无法获取屏幕";
        return;
    }

    // 截取指定区域的截图
    QPixmap pixmap = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height());

    // 将 QPixmap 转换为 QImage
    QImage image = pixmap.toImage();
    if (image.isNull()) {
        qWarning() << "截图转换为QImage失败";
        return;
    }

    // 显示到 QLabel 上，保持比例
    ui->label_gameinfo->setPixmap(pixmap.scaled(ui->label_gameinfo->size(), Qt::KeepAspectRatio));

    // 将 QImage 保存到桌面
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = desktopPath + "/1.png";

    if (!image.save(filePath)) {
        qWarning() << "保存截图失败:" << filePath;
    } else {
        qDebug() << "截图已保存到:" << filePath;
    }

    // 转换为 OpenCV Mat 进行进一步处理（可选）
    cv::Mat mat(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
    if (mat.empty()) {
        qWarning() << "OpenCV Mat 转换失败";
        return;
    }

    cv::Mat matBGR;
    cv::cvtColor(mat, matBGR, cv::COLOR_BGRA2BGR);

    // 这里可以进行其他 OpenCV 操作
}


void MainWindow::GetImage()
{
    // 截取屏幕的指定区域 (x, y, width, height)
    qDebug() <<startPos.x() << startPos.y() << endPos.x()<< endPos.y();
    QRect captureRect(startPos.x(), startPos.y(),endPos.x()-startPos.x(),endPos.y()- startPos.y());  // 设置需要截取的位置和宽高
    //QString filePath = "E:/qtpro/ScreenCapture/测试/screenshot.png";      // 设置保存路径

    captureScreenAndSave(captureRect);

}
