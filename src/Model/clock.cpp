#include "clock.h"


void Clock::TimingBegin()
{
    timer.restart();

}

qint64 Clock::TimingEnd()
{
    return timer.nsecsElapsed()/ 1000000;
}
