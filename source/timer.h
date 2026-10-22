#ifndef TIMER_H
#define TIMER_H

class Timer {

private:
    float deltaTime;
    unsigned long int currentTicks, lastTicks;

public:
    Timer();
    void update();
    float getDeltaTime();

};

#endif