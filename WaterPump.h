// WaterPump.h
#ifndef WATERPUMP_H
#define WATERPUMP_H

#include <gpiod.h>
#include <ctime>

class WaterPump {
public:
    // Constructor
    // pin: GPIO pin number
    // ignoreTimeSeconds: Time to ignore water pump activation after last activation
    WaterPump(int pin, int ignoreTimeSeconds, int pumpTimeSeconds);

    // Destructor
    ~WaterPump();

    void activate();        // Turn on water pump
    void deactivate();      // Turn off water pump
    void toggle();          // Toggle water pump status
    bool getStatus();       // Get water pump status
    void setActivationDuration(int pumpTimeSeconds);    // Set water pump activation duration
    int getActivationDuration();                // Get water pump activation duration
    int getIgnoreTime();            // Get time to ignore water pump activation after last activation

    std::tm getLastActivation();            // Get time of last activation

private:
    gpiod_chip* chip;           // GPIO chip
    gpiod_line* line;       // GPIO line
    int pinNum;                     // GPIO pin number
    bool isRunning = false;     // Water pump status
    bool activated = false;     // Water pump activation status
    std::tm lastActivation;     // Time of last activation
    int activationDuration;     // Water pump activation duration
    int ignoreTime;        // Time to ignore water pump activation after last activation
};

#endif // WATERPUMP_H
