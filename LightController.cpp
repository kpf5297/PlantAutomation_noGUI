/*
    LightController.cpp - Library for controlling a light.

    Desc:   Library for controlling lights on the Raspberry Pi using gpiod and mosfets (active high)

    g++ -I/home/kpf5297/Code/ManualControl driver.cpp Logging.cpp LightController.cpp -o D -lpigpio -lgpiod -lrt -lpthread


    Author: Kevin Fox
    Date:   23 NOV 2023

*/
#include "LightController.h"
#include <iostream>
#include <gpiod.h>

LightController::LightController(int pin, time_t &dailyOn, time_t &dailyOff) : dailyOnTime(dailyOn), dailyOffTime(dailyOff), pinNum(pin), on(false) {

    // Open the GPIO chip
    chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        std::cout << "Error opening GPIO chip" << std::endl;
        exit(1);
    }

    // Get the GPIO line
    line = gpiod_chip_get_line(chip, pinNum);
    if (!line) {
        std::cout << "Error getting GPIO line" << std::endl;
        exit(1);
    }

    // Request the GPIO line
    if (gpiod_line_request_output(line, "LightController", 0) < 0) {
        std::cout << "Error requesting GPIO line" << std::endl;
        exit(1);
    }
}

LightController::LightController(int pin) : pinNum(pin), on(false) {

    // Open the GPIO chip
    chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        std::cout << "Error opening GPIO chip" << std::endl;
        exit(1);
    }

    // Get the GPIO line
    line = gpiod_chip_get_line(chip, pinNum);
    if (!line) {
        std::cout << "Error getting GPIO line" << std::endl;
        exit(1);
    }

    // Request the GPIO line
    if (gpiod_line_request_output(line, "LightController", 0) < 0) {
        std::cout << "Error requesting GPIO line" << std::endl;
        exit(1);
    }
}

LightController::~LightController() {
    // Release the GPIO line and close the chip
    gpiod_line_release(line);
    gpiod_chip_close(chip);
}

void LightController::turnOn() {
    // Turn on the lights
    gpiod_line_set_value(line, 1);
    on = true;
}

void LightController::turnOff() {
    // Turn off the lights
    gpiod_line_set_value(line, 0);
    on = false;
}

void LightController::toggle() {
    // Toggle the lights
    if (on) {
        turnOff();
    } else {
        turnOn();
    }
}

bool LightController::isOn() {
    // Return the current state
    return on;
}

// Setters and getters for the times
void LightController::setDailyOn(time_t &time) {
    dailyOnTime = time;
}

void LightController::setDailyOff(time_t &time) {
    dailyOffTime = time;
}

time_t LightController::getDailyOn() {
    return dailyOnTime;
}

time_t LightController::getDailyOff() {
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



