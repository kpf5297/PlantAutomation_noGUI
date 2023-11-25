/*

    Implementation of the Relay class.

    // GPIO pin 17 is relay 0

*/
#include "Relay.h"

Relay::Relay(int pinNumber) {
    // Ensure that the pin number is valid
    if (pinNumber < 0 || pinNumber > 27) {
        std::cout << "Invalid pin number" << std::endl;
        exit(1);
    }

    // Set the pin number
    this->pinNum = pinNumber;

    // Open the GPIO chip
    this->chip = gpiod_chip_open("/dev/gpiochip0");

    // Get the GPIO line
    this->line = gpiod_chip_get_line(this->chip, this->pinNum);

    // Set the GPIO line to output
    gpiod_line_request_output(this->line, "Relay", 0);

    // Set the state to false
    this->state = false;
}

Relay::~Relay() {
    // Close the GPIO line
    gpiod_line_release(this->line);

    // Close the GPIO chip
    gpiod_chip_close(this->chip);
}

void Relay::setState(bool state) {
    // Set the state
    this->state = state;

    // Set the GPIO line to the state
    gpiod_line_set_value(this->line, this->state);
}

int Relay::getState() {
    // Return the state
    return this->state;
}
