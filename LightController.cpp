#include "LightController.h"

LightController::LightController(int pin, const std::tm& dailyOn, const std::tm& dailyOff) {
    // Set the pin number
    pinNum = pin;

    // Set the daily on/off times
    dailyOnTime = dailyOn;
    dailyOffTime = dailyOff;

    // Set the initial state to off
    on = false;

    // Open the chip
    chip = gpiod_chip_open("/dev/gpiochip0");

    // Get the line
    line = gpiod_chip_get_line(chip, pinNum);

    // Request the line
    gpiod_line_request_output(line, "LED", 0);
}

LightController::LightController(int pin) {
    // Set the pin number
    pinNum = pin;

    // Set the initial state to off
    on = false;

    // Open the chip
    chip = gpiod_chip_open("/dev/gpiochip0");

    // Get the line
    line = gpiod_chip_get_line(chip, pinNum);

    // Request the line
    gpiod_line_request_output(line, "LED", 0);
}

LightController::~LightController() {
    // Release the line
    gpiod_line_release(line);

    // Close the chip
    gpiod_chip_close(chip);
}

void LightController::turnOn() {
    // Turn on the lights
    gpiod_line_set_value(line, 1);

    // Set the state to on
    on = true;
}

void LightController::turnOff() {
    // Turn off the lights
    gpiod_line_set_value(line, 0);

    // Set the state to off
    on = false;
}

void LightController::toggle() {
    // Toggle the lights
    gpiod_line_set_value(line, !on);

    // Set the state to the opposite of what it was
    on = !on;
}

bool LightController::isOn() {
    // Return the state
    return on;
}

void LightController::setDailyOn(const std::tm& time) {
    // Set the daily on time
    dailyOnTime = time;
}

void LightController::setDailyOff(const std::tm& time) {
    // Set the daily off time
    dailyOffTime = time;
}

std::tm LightController::getDailyOn() {
    // Return the daily on time
    return dailyOnTime;
}

std::tm LightController::getDailyOff() {
    // Return the daily off time
    return dailyOffTime;
}

// Overloaded operators
std::ostream& operator<<(std::ostream& os, const LightController& lc) {
    os << "LightController: " << lc.pinNum << " is ";
    if (lc.on) {
        os << "on";
    } else {
        os << "off";
    }
    return os;
}