// WaterPump.cpp
#include "WaterPump.h"

/*
    Constructor
    pin: GPIO pin number
    ignoreTimeSeconds: Time to ignore water pump activation after last activation
    pumpTimeSeconds: Time to run water pump
*/
WaterPump::WaterPump(int pin, int ignoreTimeSeconds, int pumpTimeSeconds) {
    // Store the pin number
    pinNum = pin;

    // Store the activation duration
    activationDuration = pumpTimeSeconds;

    // Store the ignore time
    ignoreTime = ignoreTimeSeconds;

    // Open the GPIO chip
    chip = gpiod_chip_open("/dev/gpiochip0");

    // Get the GPIO line
    line = gpiod_chip_get_line(chip, pinNum);

    // Configure the GPIO line as an output
    gpiod_line_request_output(line, "WaterPump", 0);

    // Set the initial state of the GPIO line to low
    gpiod_line_set_value(line, 0);
}


/*
    Destructor
*/
WaterPump::~WaterPump() {
    gpiod_line_release(line);
    gpiod_chip_close(chip);
}

/*
    Turn on water pump
*/
void WaterPump::activate() {
    gpiod_line_set_value(line, 1);
    isRunning = true;
}

/*
    Turn off water pump
*/
void WaterPump::deactivate() {
    gpiod_line_set_value(line, 0);
    isRunning = false;
}

/*
    Toggle water pump status
*/
void WaterPump::toggle() {
    if (isRunning) {
        deactivate();
    } else {
        activate();
    }
}

/*
    Get water pump status
*/
bool WaterPump::getStatus() {
    return isRunning;
}

/*
    Set water pump activation duration
    pumpTimeSeconds: Time to run water pump
*/
void WaterPump::setActivationDuration(int pumpTimeSeconds) {
    activationDuration = pumpTimeSeconds;
}

/*
    Get water pump activation duration
*/
int WaterPump::getActivationDuration() {
    return activationDuration;
}


/*
    Set time to ignore water pump activation after last activation
    ignoreTimeSeconds: Time to ignore water pump activation after last activation
*/
void WaterPump::setIgnoreTime(int ignoreTimeSeconds) {
    ignoreTime = ignoreTimeSeconds;
}

/*
    Get time to ignore water pump activation after last activation
*/
int WaterPump::getIgnoreTime() {
    return ignoreTime;
}

