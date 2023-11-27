// LightController.cpp
#include "LightController.h"


/*
    Constructor
    pin: GPIO pin number
    dailyOn: Time to turn on light after activation
    dailyOff: Time to turn off light after activation
*/
LightController::LightController(int pin, const time_t& dailyOn, const time_t& dailyOff) {
    // Set GPIO pin number
    pinNum = pin;

    // Set daily on and off times
    dailyOnTime = dailyOn;
    dailyOffTime = dailyOff;

    // Set light status
    on = false;

    // Open GPIO chip
    chip = gpiod_chip_open("/dev/gpiochip0");

    // Request GPIO line
    line = gpiod_chip_get_line(chip, pinNum);

    // Set GPIO line direction to output
    gpiod_line_request_output(line, "LightController", 0);

    // Turn off light
    gpiod_line_set_value(line, 0);
}

/*
    Overloaded Constructor
    pin: GPIO pin number
*/
LightController::LightController(int pin) {
    // Set GPIO pin number
    pinNum = pin;

    // Set light status
    on = false;

    // Open GPIO chip
    chip = gpiod_chip_open("/dev/gpiochip0");

    // Request GPIO line
    line = gpiod_chip_get_line(chip, pinNum);

    // Set GPIO line direction to output
    gpiod_line_request_output(line, "LightController", 0);

    // Turn off light
    gpiod_line_set_value(line, 0);
}


/*
    Destructor
*/
LightController::~LightController() {
    // Close GPIO chip
    gpiod_chip_close(chip);

    // Free GPIO line
    gpiod_line_release(line);
}


/*
    Turn on light
*/
void LightController::turnOn() {
    // Turn on light
    gpiod_line_set_value(line, 1);

    // Set light status
    on = true;
}


/*
    Turn off light
*/
void LightController::turnOff() {
    // Turn off light
    gpiod_line_set_value(line, 0);

    // Set light status
    on = false;
}


/*
    Toggle light status
*/
void LightController::toggle() {
    // Toggle light status
    if (on) {
        turnOff();
    } else {
        turnOn();
    }

    // Set light status
    on = !on;
}


/*
    Get light status
*/
bool LightController::isOn() {
    return on;
}


/*
    Set time to turn on light after activation
    time: Time to turn on light after activation
*/
void LightController::setDailyOn(const time_t time) {
    dailyOnTime = time;
}


/*
    Set time to turn off light after activation
    time: Time to turn off light after activation
*/
void LightController::setDailyOff(const time_t time) {
    dailyOffTime = time;
}


/*
    Get time to turn on light after activation
*/
time_t LightController::getDailyOnTime() {
    return dailyOnTime;
}


/*
    Get time to turn off light after activation
*/
time_t LightController::getDailyOffTime() {
    return dailyOffTime;
}


