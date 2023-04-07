#ifndef __COMMON_TIMER_H__
#define __COMMON_TIMER_H__

#include <sys/time.h>

namespace common
{

// 实现定时器中断
class Timer 
{
public:
    Timer(float period = 1.0);

    void Init(float period = 1.0);

    bool IsTimeOut();
private:
    float period_; // 间隔时间: 单位秒
    struct timeval last_time_;
};

}

#endif // __COMMON_TIMER_H__