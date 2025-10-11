#ifndef CLOCK_H
#define CLOCK_H
#include <Qt>
#include <chrono>

class Clock
{
    using HRClock = std::chrono::high_resolution_clock;
    using Time = std::chrono::time_point<HRClock>;
public:
    Clock();
    qreal mark();
private:
    Time _start;
};

#endif
