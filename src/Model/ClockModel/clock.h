#ifndef CLOCK_H
#define CLOCK_H
#include <QElapsedTimer>

class Clock
{
public:
    static void TimingBegin();
    static qint64  TimingEnd();
    inline static QElapsedTimer timer;
};

#endif // CLOCK_H
