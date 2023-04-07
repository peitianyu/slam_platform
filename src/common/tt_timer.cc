#include"tt_timer.h"
#include <string>

namespace common
{


Timer::Timer(float period) : period_(period) {}

void Timer::Init(float period)
{
    period_ = period;
    gettimeofday(&last_time_, NULL);
}

bool Timer::IsTimeOut()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    if (now.tv_sec - last_time_.tv_sec >= period_)
    {
        last_time_ = now;
        return true;
    }
    return false;
}


}
