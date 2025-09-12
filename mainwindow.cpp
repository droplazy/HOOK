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
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>
#include "opencv_thread.h"
#include "display_widget.h"


QPoint mousePos(0, 0);
QPoint startPos(0, 0);
QPoint endPos(0, 0);
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
            qDebug() << "Left mouse button released at:" << releasePos;
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


    //qDebug() <<info;
    ui->label_sysinfor->setText(info);  // 显示在QLabel中
      //if(streamOn)
      //ImageStream();
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
    p_opencv = new opencv_thread();

    connect(this, SIGNAL(DebugPress(void)), p_opencv, SLOT(testSLot(void)), Qt::AutoConnection);

    p_opencv ->start();
    w_displayTest = new Display_Widget(this);
    connect(p_opencv, SIGNAL(getPic(QImage)), w_displayTest, SLOT(displayInstace(QImage)), Qt::AutoConnection);//持续推流信号
   // connect(w_displayTest, SIGNAL(closeSig(void)), this, SLOT(displayInstace(QImage)), Qt::AutoConnection);//

    w_displayTest->show();
}

MainWindow::~MainWindow()
{
    removeMouseHook();  // 移除钩子

    delete ui;
}



void MainWindow::on_pushButton_capture_clicked()//开始截屏的按钮
{


        isCpature = true;
        ui->pushButton_capture->setStyleSheet("background-color: rgb(255, 1, 1);");

}






void MainWindow::on_pushButton_imgtest_clicked()//显示测试按钮
{
    if(streamOn)
    {
        w_displayTest->deleteLater();
        streamOn =false;

    }
    else
    {

        w_displayTest = new Display_Widget();
        connect(p_opencv, SIGNAL(getPic(QImage)), w_displayTest, SLOT(displayInstace(QImage)), Qt::AutoConnection);
        w_displayTest->show();
        streamOn= true;
    }
}


void MainWindow::on_pushButton_capture_2_clicked()//截屏测试按钮
{
    ui->pushButton_capture->setStyleSheet("background-color: rgb(255, 255, 255);");


        p_opencv->ZeroPos = startPos;
        p_opencv->EndPos = endPos;
        p_opencv->startDispose = true;
        streamOn = true;

}
void MainWindow::on_pushButton_START_clicked()
{


}

void MainWindow::ChindWidegtClosed()
{
    streamOn = false;
}

