#include "Clock.h"

Clock::Clock()
{
    _start = HRClock::now();
}

qreal Clock::mark()
{
    using Duration = std::chrono::duration<qreal>;
    auto end = HRClock::now();
    Duration elapsed = end-_start;
    _start = end;
    return elapsed.count();
}
