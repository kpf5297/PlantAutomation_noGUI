#include "WaterPump.h"

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


WaterPump::~WaterPump() {
    gpiod_line_release(line);
    gpiod_chip_close(chip);
}

void WaterPump::activate() {
    gpiod_line_set_value(line, 1);
    isRunning = true;

    // Update the last activation time
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeInfo = std::localtime(&currentTime);
    lastActivation = *timeInfo;
}

void WaterPump::deactivate() {
    gpiod_line_set_value(line, 0);
    isRunning = false;
}

void WaterPump::toggle() {
    if (isRunning) {
        deactivate();
    } else {
        activate();
    }
}

bool WaterPump::getStatus() {
    return isRunning;
}

void WaterPump::setActivationDuration(int pumpTimeSeconds) {
    activationDuration = pumpTimeSeconds;
}

int WaterPump::getActivationDuration() {
    return activationDuration;
}

std::tm WaterPump::getLastActivation() {
    return lastActivation;
}

int WaterPump::getIgnoreTime() {
    return ignoreTime;
}


