/*
    LightController.h - 
    
    Desc:   Library for controlling lights on the Raspberry Pi using gpiod and mosfets (active high)

    Author: Kevin Fox
    Date:   23 NOV 2023

*/
#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <gpiod.h>
#include <ctime>

class LightController {
public:
    // LightController(int pin, time_t &dailyOn, time_t &duration);
    LightController(int pin, time_t &dailyOn, time_t &dailyOff);
    LightController(int pin);
    ~LightController();

    void turnOn();
    void turnOff();
    void toggle();
    bool isOn();
    void setDailyOn(time_t &time);
    void setDailyOff(time_t &time);
    void setDuration(time_t &time);
    time_t getDailyOn();
    time_t getDailyOff();
    time_t getDuration();

private:
    gpiod_chip *chip;
    gpiod_line *line;
    int pinNum;
    bool on;

    time_t dailyOnTime;
    time_t dailyOffTime;
    time_t duration;
};

#endif // LIGHTCONTROLLER_H
