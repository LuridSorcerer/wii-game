#include "timer.h"

#include <gccore.h>
#include <ogc/lwp_watchdog.h>

Timer::Timer() {
    currentTicks = lastTicks = gettime();
}

void Timer::update() {
    lastTicks = currentTicks;
    currentTicks = gettime();
    deltaTime = ((currentTicks - lastTicks) / (float)TB_TIMER_CLOCK ) / 1000;
}

float Timer::getDeltaTime() {
    return deltaTime;
}