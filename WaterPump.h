// WaterPump.h
#ifndef WATERPUMP_H
#define WATERPUMP_H

#include <gpiod.h>
#include <ctime>

class WaterPump {
public:
    WaterPump(int pin, int ignoreTimeSeconds, int pumpTimeSeconds);
    ~WaterPump();

    void activate();
    void deactivate();
    void toggle();
    bool getStatus();
    void setActivationDuration(int pumpTimeSeconds);
    int getActivationDuration();
    std::tm getLastActivation();

private:
    gpiod_chip* chip;
    gpiod_line* line;
    int pinNum;
    bool isRunning = false;
    bool activated = false;
    std::tm lastActivation;
    int activationDuration;
    int ignoreTime;
};

#endif // WATERPUMP_H
