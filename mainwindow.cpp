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
#include "event_pthread.h"
#include <ProDefine.h>
#include "display_widget.h"




QPoint ZeroPos(0, 0);
QPoint EndPos(0, 0);

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
void moveMouseAndClick(int x, int y,QString L_R) {
    // 设置鼠标位置
    SetCursorPos(x, y);

    if(L_R == "left")
    {
    // 模拟鼠标按下事件
    mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);

    // 模拟鼠标抬起事件
    mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
    }
    else if(L_R == "right")
    {
        // 模拟鼠标按下事件
        mouse_event(MOUSEEVENTF_RIGHTDOWN, x, y, 0, 0);

        // 模拟鼠标抬起事件
        mouse_event(MOUSEEVENTF_RIGHTUP, x, y, 0, 0);
    }
    else
    {
        qDebug()<< "error click !\n";
    }
    qDebug() << "Mouse moved and clicked at:" << QPoint(x, y);
}
// 自动移动鼠标但不点击
void moveMouseOnly(int x, int y) {
    // 设置鼠标位置
    SetCursorPos(x, y);

    // 打印鼠标移动的位置
   // qDebug() << "Mouse moved to:" << QPoint(x, y);
}

void MainWindow::updateWindowInfo()
{



      QString info = QString("Mouse : %1 x %2").arg(mousePos.x()).arg(mousePos.y())+\
                   "    "+QString("start : %1 x %2").arg(startPos.x()).arg(startPos.y())+\
                   "    "+QString("end : %1 x %2").arg(endPos.x()).arg(endPos.y());


    //qDebug() <<info;
    ui->label_sysinfor->setText(info);  // 显示在QLabel中
      QString characterInfo = "地点 : " + p_thread->t_loaction  +"\n "+"坐标:" +p_thread->t_position+"\n ";
      ui->textEdit->setText(characterInfo);
}
#include <QRandomGenerator>

void MainWindow::MoveMouserToTarget()
{
    if (!p_thread->MouseNeedMove)
        return;

    // 获取当前鼠标位置
    POINT currentPos;
    if (GetCursorPos(&currentPos)) {
        // 打印当前位置
       // qDebug() << "\rCurrent mouse position:" << QPoint(currentPos.x, currentPos.y);

        // 获取目标点击位置
        QPoint target = p_thread->TargetClick;

        // 计算x, y方向上的差距
        int dx = target.x() - currentPos.x;
        int dy = target.y() - currentPos.y;

        // 如果目标与当前位置非常接近，直接停止
        if (abs(dx) < 1 && abs(dy) < 1) {
            SetCursorPos(target.x(), target.y());  // 确保最后一次设置目标位置
            p_thread->MouseNeedMove = false;
         //   qDebug() << "\rMouse reached the target:" << target;
            //p_thread->MouseNeedMove =true;
            return;
        }

        // 计算每次移动的步长
        int stepX = (dx != 0) ? (dx / abs(dx)) : 0;  // 正负方向
        int stepY = (dy != 0) ? (dy / abs(dy)) : 0;  // 正负方向

        // 添加随机抖动，模拟不规则的移动
        QRandomGenerator *rng = QRandomGenerator::global();
        int jitterX = rng->bounded(-2, 3);  // 范围是 -2 到 2 像素
        int jitterY = rng->bounded(-2, 3);  // 范围是 -2 到 2 像素

        // 每次移动少量距离（1像素），并加入抖动
        currentPos.x += stepX + jitterX;
        currentPos.y += stepY + jitterY;

        // 移动鼠标到新的位置
        SetCursorPos(currentPos.x, currentPos.y);

        // 打印移动后的鼠标位置
       // qDebug() << "\rMouse moved to:" << QPoint(currentPos.x, currentPos.y);

        // 在下一次调用时继续移动，直到到达目标
    }
    else {
        qDebug() << "\rFailed to get cursor position!";
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateWindowInfo);
    timer->start(10); // 每秒更新一次
    QTimer *timer_msr = new QTimer(this);
    connect(timer_msr, &QTimer::timeout, this, &MainWindow::MoveMouserToTarget);
    timer_msr->start(1); // 每秒更新一次
    installMouseHook();  // 安装鼠标钩子

    // 启动定时器，10秒后退出程序
    //  QTimer::singleShot(10000, this, &TransparentWindow::closeApp);

    // 自动将鼠标移到指定位置 (例如：屏幕中心)
  //  moveMouseAndClick(422, 453,"left");  // 可以根据需要修改目标位置
    p_thread = new event_pthread(this);

  //  connect(this, SIGNAL(DebugPress(void)), p_opencv, SLOT(testSLot(void)), Qt::AutoConnection);

    p_thread ->start();
    w_displayTest = new Display_Widget(this);
    connect(p_thread, SIGNAL(getPic(QImage)), w_displayTest, SLOT(displayInstace(QImage)), Qt::AutoConnection);//持续推流信号
    connect(p_thread, SIGNAL(regnize(QString)), this, SLOT(GetNeedRegnizePic(QString)), Qt::AutoConnection);//持续推流信号

    w_displayTest->show();

    p_http = new HttpClient();
}

MainWindow::~MainWindow()
{
    removeMouseHook();  // 移除钩子

    delete ui;
}

#include <QUrlQuery>

#define PIC_REGNIZE "https://cn.apihz.cn/api/ai/shituwen.php"
#define API_ID     "10001671"
#define API_KEY    "HangZhoufogkniteleElectron950905"

void MainWindow::GetORCRegnizeToNetwork(QString picBase64)
{

    QUrl url(PIC_REGNIZE);
    QUrlQuery query;
    query.addQueryItem("id", API_ID);
    query.addQueryItem("key", API_KEY);
    query.addQueryItem("type", "2");
    query.addQueryItem("img", picBase64);
    //   query.addQueryItem("words", "心灵鸡汤");

    url.setQuery(query); // 设置 URL 的查询部分
    p_http->sendGetRequest(url);
}

void MainWindow::GetNeedRegnizePic(QString picBase64)
{
    GetORCRegnizeToNetwork(picBase64);
}

void MainWindow::on_pushButton_capture_clicked()//开始截屏的按钮
{


        isCpature = true;
        ui->pushButton_capture->setStyleSheet("background-color: rgb(255, 1, 1);");

}






void MainWindow::on_pushButton_imgtest_clicked()//显示测试按钮
{
    if(p_thread->streamOn)
    {
        w_displayTest->deleteLater();
        p_thread->streamOn =false;

    }
    else
    {

        w_displayTest = new Display_Widget();
      //  connect(p_opencv, SIGNAL(getPic(QImage)), w_displayTest, SLOT(displayInstace(QImage)), Qt::AutoConnection);
        w_displayTest->show();
        p_thread->streamOn= true;
    }
}


void MainWindow::on_pushButton_capture_2_clicked()//截屏测试按钮 完成
{
    ui->pushButton_capture->setStyleSheet("background-color: rgb(255, 255, 255);");
    ZeroPos = startPos;
    EndPos = endPos;
        p_thread->streamOn = true;

}
void MainWindow::on_pushButton_START_clicked()
{


}

void MainWindow::ChindWidegtClosed()
{
    p_thread->streamOn = false;
}

