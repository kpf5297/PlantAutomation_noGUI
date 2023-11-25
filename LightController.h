// LightController.h
#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <gpiod.h>
#include <iostream>
#include <ctime>

class LightController {
public:
    LightController(int pin, const std::tm& dailyOn, const std::tm& dailyOff);
    LightController(int pin);
    ~LightController();

    void turnOn();
    void turnOff();
    void toggle();
    bool isOn();
    void setDailyOn(const std::tm& time);
    void setDailyOff(const std::tm& time);
    std::tm getDailyOn();
    std::tm getDailyOff();

    // Overloaded operators
    friend std::ostream& operator<<(std::ostream& os, const LightController& lc);

private:
    gpiod_chip *chip;
    gpiod_line *line;
    int pinNum;
    bool on;

    std::tm dailyOnTime;
    std::tm dailyOffTime;
};

#endif // LIGHTCONTROLLER_H