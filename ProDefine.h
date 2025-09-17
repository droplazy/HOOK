#ifndef PRODEFINE_H
#define PRODEFINE_H

#include <QPoint>


extern QPoint ZeroPos;
extern QPoint EndPos;
// 枚举类型，表示四种状态
enum class Task_State
{
    IDLE,
    QINGLONG, // 青龙
    XUANWU,   // 玄武
    ZHUQUE,   // 朱雀
    SHIMEN    // 石门
};
#endif // PRODEFINE_H
