#ifndef PRODEFINE_H
#define PRODEFINE_H

#include <QPoint>
#include <QString>

extern QPoint ZeroPos;
extern QPoint EndPos;
extern QStringList dreamWorldLocations;

// 枚举类型，表示四种状态
enum class Task_State
{
    MOUSER_OFFSET,
    IDLE,
    QINGLONG, // 青龙
    XUANWU,   // 玄武
    ZHUQUE,   // 朱雀
    SHIMEN    // 石门
};
enum class QINGLONG_Task
{
    IDLE,
    GetTask
};
enum HTTP_TYPE {
    ORCregnize,
    HOT_SEACH_WEIBO,
    HOT_SEACH_DOUYIN,
    PICTURE_BAIDU,
    PICTURE_SOUGOU,
    ONE_WORD,
    IP_QUERY,
    HISTORY_TODAY,
    WEATHER_IP,
    PICTURE_DOWNLOAD,
    HOTSEARCH,
    DATETODAY,
    WEATHERTODAY,
    UNKNOW_OPT //9
};

struct S_HTTP_RESPONE {
    //QString Title;
    bool  success;
    QString Message;
    HTTP_TYPE Title;
    QString url;
    QByteArray bytes;
    QString Error;
    /*void print() const {
        //qDebug() << "Title:" << Title;
        qDebug() << "success:" << success;
        qDebug() << "Message:" << Message;
        qDebug() << "url:" << url;
        qDebug() << "Error:" << Error;

    }*/
};

// 按下并释放指定键（单键或组合键）
void releaseKey(const QString& key) ;
void pressKey(const QString& key) ;
void moveMouseOnly(int x, int y);
QPoint  convertCoordinates(const QPoint& canvasOffset, const QPoint& targetCenter);
QString findMostSimilarLocation(const QString &input, const QStringList &locationList, int maxDistance = 3);
void moveMouseAndClick(int x, int y,QString L_R) ;
#endif // PRODEFINE_H
