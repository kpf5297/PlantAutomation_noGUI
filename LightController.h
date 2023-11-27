// LightController.h
#ifndef LIGHTCONTROLLER_H
#define LIGHTCONTROLLER_H

#include <gpiod.h>
#include <ctime>

class LightController {
public:
    // Constructor
    // pin: GPIO pin number
    // dailyOn: Time to turn on light after activation
    // dailyOff: Time to turn off light after activation
    LightController(int pin, const time_t& dailyOn, const time_t& dailyOff);

    // Overloaded Constructor
    // pin: GPIO pin number
    LightController(int pin);

    // Destructor
    ~LightController();

    void turnOn();                              // Turn on light
    void turnOff();                             // Turn off light
    void toggle();                              // Toggle light status
    bool isOn();                                // Get light status
    void setDailyOn(const time_t time);         // Set time to turn on light after activation
    void setDailyOff(const time_t time);        // Set time to turn off light after activation
    time_t getDailyOnTime();                    // Get time to turn on light after activation
    time_t getDailyOffTime();                   // Get time to turn off light after activation

    // Overloaded operators for debugging
    friend std::ostream& operator<<(std::ostream& os, const LightController& lc);

private:
    gpiod_chip *chip;       // GPIO chip
    gpiod_line *line;       // GPIO line
    int pinNum;             // GPIO pin number
    bool on;                // Light status
    time_t dailyOnTime;     // Time to turn on light after activation
    time_t dailyOffTime;    // Time to turn off light after activation
};

#endif // LIGHTCONTROLLER_H