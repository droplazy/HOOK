#include "event_pthread.h"
#include "opencv_utils.h"
#include <QDebug>

event_pthread::event_pthread(QObject *parent)
    : QThread(parent), currentState(Task_State::IDLE)  // 默认状态为 IDLE
{
}

void event_pthread::run()
{
    while (!isInterruptionRequested()) // 检查线程是否请求中断
    {
        switch (currentState) {
        case Task_State::QINGLONG:
            qDebug() << "State is QINGLONG";

            break;
        case Task_State::XUANWU:
            qDebug() << "State is XUANWU";
            // 执行与 XUANWU 状态相关的操作
            break;
        case Task_State::ZHUQUE:
            qDebug() << "State is ZHUQUE";
            // 执行与 ZHUQUE 状态相关的操作
            break;
        case Task_State::SHIMEN:
            qDebug() << "State is SHIMEN";
            // 执行与 SHIMEN 状态相关的操作
            break;
        case Task_State::IDLE:
            qDebug() << "State is IDLE";
            GetIdleImage();
            break;
        default:
            qDebug() << "Unknown state!";
            break;
        }

        // 模拟一些需要定时处理的任务，比如等待一段时间
        //QThread::msleep(1);  // 让线程休眠一秒，防止占用过多CPU资源
    }
}
#include <QElapsedTimer>

void event_pthread::GetIdleImage()
{
    opencv_utils::disposeIMGformessage();

    //获得IMG 格式的窗口
    QRect captureRect(ZeroPos.x(), ZeroPos.y(),EndPos.x()-ZeroPos.x(),EndPos.y()- ZeroPos.y());  // 设置需要截取的位置和宽高
    QImage img = opencv_utils::captureScreenQimage(captureRect);
    if (streamOn) {
        // 发送 img 图像
        emit getPic(img.copy());
        qDebug() << "Sending image with dimensions: " << img.width() << "x" << img.height();
    }
}

#if 0
    // 将 QImage 转换为 cv::Mat
    //opencv_utils::disposeIMGformessage();
    qDebug() << "ZeroPos: (" << ZeroPos.x() << "," << ZeroPos.y() << ")";
    qDebug() << "EndPos: (" << EndPos.x() << "," << EndPos.y() << ")";

    cv::Mat targetImg = opencv_utils::captureGameWindow();

    QRect rect(+53, +205, 138, 20);
    cv::Mat posText = opencv_utils::capturePositionForRect(rect);

    // 开始计时
    QElapsedTimer timer;
    timer.start();

    // 执行 FindPicTarget 接口
    QImage img = opencv_utils::FindPicTarget(targetImg, posText);

    // 计算耗时
    qint64 elapsed = timer.elapsed();  // 获取执行时间（单位：毫秒）

    // 输出耗时
    qDebug() << "FindPicTarget executed in" << elapsed << "milliseconds";

    // 检查 streamOn 是否为 true，并发送图像
    if (streamOn) {
        // 发送 img 图像
        emit getPic(img.copy());
        qDebug() << "Sending image with dimensions: " << img.width() << "x" << img.height();
    }
#endif


void event_pthread::setState(Task_State state)
{
    currentState = state;
}

Task_State event_pthread::getState() const
{
    return currentState;
}
