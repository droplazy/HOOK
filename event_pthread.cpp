
#include <Windows.h>//必须位于OPENCV上
#include "event_pthread.h"
#include "opencv_utils.h"
#include <QDebug>
#include <QMap>
// 按下并释放指定键（单键或组合键）
void releaseKey(const QString& key) ;
void pressKey(const QString& key) ;

event_pthread::event_pthread(QObject *parent)
    : QThread(parent), currentState(Task_State::QINGLONG)  // 默认状态为 IDLE
{
#if 0
    QTimer *timer_orc = new QTimer(this);
    connect(timer_orc, &QTimer::timeout, this, [=]() {
        GameGiveObject();

        moveMouseAndClick(-1320,920,"right");

    });
    timer_orc->start(3000);
#endif
}

void event_pthread::run()
{
    while (!isInterruptionRequested()) // 检查线程是否请求中断
    {
        if(!IsCorrectScreen())
            continue;

        GetCharacterForTess();


        switch (currentState) {
        case Task_State::QINGLONG:
            QingLongTask();

            break;
        case Task_State::XUANWU:
           // qDebug() << "State is XUANqU";
            // 执行与 XUANWU 状态相关的操作
            break;
        case Task_State::ZHUQUE:
           // qDebug() << "State is ZHUQUE";
            // 执行与 ZHUQUE 状态相关的操作
            break;
        case Task_State::SHIMEN:
           // qDebug() << "State is SHIMEN";
            // 执行与 SHIMEN 状态相关的操作
            break;
        case Task_State::IDLE:
           // qDebug() << "State is IDLE";
            GetIdleImage();
            break;
        default:
           // qDebug() << "Unknown state!";
            break;
        }

        // 模拟一些需要定时处理的任务，比如等待一段时间
        QThread::msleep(350);  // 让线程休眠一秒，防止占用过多CPU资源
    }
}
#include <QElapsedTimer>

bool event_pthread::IsCorrectScreen()
{
    return (std::abs(EndPos.x() - ZeroPos.x()) > 100 && std::abs(EndPos.y() - ZeroPos.y()) > 100);
}

void event_pthread::GetGameScreen()
{
    QRect captureRect(ZeroPos.x(), ZeroPos.y(),EndPos.x()-ZeroPos.x(),EndPos.y()- ZeroPos.y());  // 设置需要截取的位置和宽高
    QImage img = opencv_utils::captureScreenQimage(captureRect);
    if (streamOn) {
        // 发送 img 图像
        emit getPic(img.copy());
        qDebug() << "Sending image with dimensions: " << img.width() << "x" << img.height();
    }
}
void event_pthread::QingLongTask()
{
    QImage qImage(":/Element/QingLong/GetNPC.png");
    findNpcForScreen(qImage);
}


void event_pthread::findNpcForScreen(QImage image)
{
    cv::Mat targetImg = opencv_utils::captureGameWindow();

    // 从资源路径加载图片

    //QImage qImage(":/Element/QingLong/GetNPC.png");

    // 将 QImage 转换为 cv::Mat
    cv::Mat posText = opencv_utils::QImageToMat(image);  // 假设你已经实现了 QImageToMat 函数

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
}

void event_pthread::GetIdleImage()
{
    //opencv_utils::disposeIMGformessage();
    if(!IsCorrectScreen())
        return ;
    //获得IMG 格式的窗口
    GetGameScreen();

}
void event_pthread::GetCharacterForTess()
{
   // qDebug() << "ZeroPos: (" << ZeroPos.x() << "," << ZeroPos.y() << ")";
   // qDebug() << "EndPos: (" << EndPos.x() << "," << EndPos.y() << ")";

    // cv::Mat targetImg = captureGameWindow();
    //  cv::Mat templateImg =capturePosition();

   // qDebug() << "****************************************************";
    QRect rect(+53,+207,138,20);
    cv::Mat posText = opencv_utils::capturePositionForRect(rect);
    QString position=opencv_utils::recognizeTextFromMat(posText,OCR_ENGLISH);

    rect.setRect(+45,+116,115,35);
    posText = opencv_utils::capturePositionForRect(rect);
    QString location =   opencv_utils::recognizeTextFromMat(posText,OCR_CHINESE_SIMPLE);
    QString result = findMostSimilarLocation(location, dreamWorldLocations);

    //qDebug()<< "最相似的地名是: " << result << "OCR:"<<position;
    t_loaction = result;
    t_position = position;
 //   return ("location"+result+"pos:"+position);
}

void event_pthread::GameopenTaskMenu()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("q");
    QThread::msleep(50);
    releaseKey("q");
    QThread::msleep(50);
    releaseKey("alt");
}

void event_pthread::GameGiveObject()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("g");
    QThread::msleep(50);
    releaseKey("g");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::GameAttack()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("a");
    QThread::msleep(50);
    releaseKey("a");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::GameOpenInventoryMenu()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("e");
    QThread::msleep(50);
    releaseKey("e");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::GameGroup()
{
    //holdKey1();
    pressKey("alt");
    QThread::msleep(50);
    pressKey("t");
    QThread::msleep(50);
    releaseKey("t");
    QThread::msleep(50);
    releaseKey("alt");
}
void event_pthread::GetCharacterPostion()
{
    QRect rect(+53,+207,138,20);
    cv::Mat posText = opencv_utils::capturePositionForRect(rect);
    //QString position=recognizeTextFromMat(posText,OCR_ENGLISH);
    QString base64pic=  opencv_utils::recognizeTextFromMatBackBase(posText);
    // qDebug() << "**************************************\n";
    // qDebug() << base64pic;
    // qDebug() << "**************************************\n";
    emit regnize(base64pic);
}
void event_pthread::GetCharacterLocation()
{

    QRect rect(+45,+120,115,30);
    cv::Mat posText = opencv_utils::capturePositionForRect(rect);
    //QString position=recognizeTextFromMat(posText,OCR_ENGLISH);
    QString base64pic=  opencv_utils::recognizeTextFromMatBackBase(posText);
    // qDebug() << "**************************************\n";
    // qDebug() << base64pic;
    // qDebug() << "**************************************\n";
    emit regnize(base64pic);
}
void event_pthread::GetCharacterlocInfo()
{

    GetCharacterLocation();
    GetCharacterPostion();
}



void event_pthread::setState(Task_State state)
{
    currentState = state;
}

Task_State event_pthread::getState() const
{
    return currentState;
}

void pressKey(const QString& key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;

    // 将输入的键转换为小写，避免区分大小写
    QString lowerKey = key.toLower();

    // 字母 a~z 和 数字 1~9 键映射
    QMap<QString, WORD> keyMap = {
        {"a", 0x41}, {"b", 0x42}, {"c", 0x43}, {"d", 0x44}, {"e", 0x45}, {"f", 0x46},
        {"g", 0x47}, {"h", 0x48}, {"i", 0x49}, {"j", 0x4A}, {"k", 0x4B}, {"l", 0x4C},
        {"m", 0x4D}, {"n", 0x4E}, {"o", 0x4F}, {"p", 0x50}, {"q", 0x51}, {"r", 0x52},
        {"s", 0x53}, {"t", 0x54}, {"u", 0x55}, {"v", 0x56}, {"w", 0x57}, {"x", 0x58},
        {"y", 0x59}, {"z", 0x5A}, {"1", 0x31}, {"2", 0x32}, {"3", 0x33}, {"4", 0x34},
        {"5", 0x35}, {"6", 0x36}, {"7", 0x37}, {"8", 0x38}, {"9", 0x39}, {"0", 0x30}
    };

    // 功能键 F1~F12 键映射
    QMap<QString, WORD> fKeyMap = {
        {"f1", VK_F1}, {"f2", VK_F2}, {"f3", VK_F3}, {"f4", VK_F4}, {"f5", VK_F5},
        {"f6", VK_F6}, {"f7", VK_F7}, {"f8", VK_F8}, {"f9", VK_F9}, {"f10", VK_F10},
        {"f11", VK_F11}, {"f12", VK_F12}
    };

    // 特殊键：ALT, SHIFT, CTRL, BACKSPACE
    QMap<QString, WORD> specialKeyMap = {
        {"alt", VK_MENU}, {"shift", VK_SHIFT}, {"ctrl", VK_CONTROL}, {"backspace", VK_BACK}
    };

    // 如果是单个键，直接处理
    if (keyMap.contains(lowerKey)) {
        input.ki.wVk = keyMap[lowerKey];
        input.ki.dwFlags = 0;  // 按下事件
        SendInput(1, &input, sizeof(INPUT));  // 发送按下事件
        qDebug() << "Pressed" << key << "key...";  // 输出调试信息
    }
    else if (fKeyMap.contains(lowerKey)) {
        input.ki.wVk = fKeyMap[lowerKey];
        input.ki.dwFlags = 0;  // 按下事件
        SendInput(1, &input, sizeof(INPUT));  // 发送按下事件
        qDebug() << "Pressed" << key << "key...";  // 输出调试信息
    }
    else if (specialKeyMap.contains(lowerKey)) {
        input.ki.wVk = specialKeyMap[lowerKey];
        input.ki.dwFlags = 0;    // 按下事件
        SendInput(1, &input, sizeof(INPUT));  // 发送按下事件
        qDebug() << "Pressed" << key << "key...";  // 输出调试信息
    }
    else {
        qDebug() << "Invalid key specified!";
    }
}

void releaseKey(const QString& key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;

    // 将输入的键转换为小写，避免区分大小写
    QString lowerKey = key.toLower();

    // 字母 a~z 和 数字 1~9 键映射
    QMap<QString, WORD> keyMap = {
        {"a", 0x41}, {"b", 0x42}, {"c", 0x43}, {"d", 0x44}, {"e", 0x45}, {"f", 0x46},
        {"g", 0x47}, {"h", 0x48}, {"i", 0x49}, {"j", 0x4A}, {"k", 0x4B}, {"l", 0x4C},
        {"m", 0x4D}, {"n", 0x4E}, {"o", 0x4F}, {"p", 0x50}, {"q", 0x51}, {"r", 0x52},
        {"s", 0x53}, {"t", 0x54}, {"u", 0x55}, {"v", 0x56}, {"w", 0x57}, {"x", 0x58},
        {"y", 0x59}, {"z", 0x5A}, {"1", 0x31}, {"2", 0x32}, {"3", 0x33}, {"4", 0x34},
        {"5", 0x35}, {"6", 0x36}, {"7", 0x37}, {"8", 0x38}, {"9", 0x39}, {"0", 0x30}
    };

    // 功能键 F1~F12 键映射
    QMap<QString, WORD> fKeyMap = {
        {"f1", VK_F1}, {"f2", VK_F2}, {"f3", VK_F3}, {"f4", VK_F4}, {"f5", VK_F5},
        {"f6", VK_F6}, {"f7", VK_F7}, {"f8", VK_F8}, {"f9", VK_F9}, {"f10", VK_F10},
        {"f11", VK_F11}, {"f12", VK_F12}
    };

    // 特殊键：ALT, SHIFT, CTRL, BACKSPACE
    QMap<QString, WORD> specialKeyMap = {
        {"alt", VK_MENU}, {"shift", VK_SHIFT}, {"ctrl", VK_CONTROL}, {"backspace", VK_BACK}
    };

    // 如果是单个键，直接处理
    if (keyMap.contains(lowerKey)) {
        input.ki.wVk = keyMap[lowerKey];
        input.ki.dwFlags = KEYEVENTF_KEYUP;  // 松开事件
        SendInput(1, &input, sizeof(INPUT));  // 发送松开事件
        qDebug() << "Released" << key << "key.";  // 输出调试信息
    }
    else if (fKeyMap.contains(lowerKey)) {
        input.ki.wVk = fKeyMap[lowerKey];
        input.ki.dwFlags = KEYEVENTF_KEYUP;  // 松开事件
        SendInput(1, &input, sizeof(INPUT));  // 发送松开事件
        qDebug() << "Released" << key << "key.";  // 输出调试信息
    }
    else if (specialKeyMap.contains(lowerKey)) {
        input.ki.wVk = specialKeyMap[lowerKey];
        input.ki.dwFlags = KEYEVENTF_KEYUP;    // 松开事件
        SendInput(1, &input, sizeof(INPUT));  // 发送松开事件
        qDebug() << "Released" << key << "key.";  // 输出调试信息
    }
    else {
        qDebug() << "Invalid key specified!";
    }
}

