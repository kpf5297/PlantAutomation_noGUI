/*
    Compile with:   g++ -I/home/kpf5297/Code/ManualControl driver.cpp Logging.cpp LightController.cpp -o D -lgpiod -lrt -lpthread

*/

#include <unistd.h>
#include <iostream>
#include "Logging.h"
#include "LightController.h"

int BLUE_LED_PIN = 17;
int GREEN_LED_PIN = 27;
int LOOP_COUNT = 3;

int main() {

    // Set daily on/off time for the current date
    time_t dailyOnTime = time(NULL);
    time_t dailyOffTime = time(NULL);
    struct tm *onTime = localtime(&dailyOnTime);
    struct tm *offTime = localtime(&dailyOffTime);
    onTime->tm_hour = 3;
    onTime->tm_min = 39;
    onTime->tm_sec = 0;
    offTime->tm_hour = 03;
    offTime->tm_min = 49;
    offTime->tm_sec = 30;
    dailyOnTime = mktime(onTime);
    dailyOffTime = mktime(offTime);

    time_t currentTime = time(NULL);


    // Create a logger
    Logger logger;

    // Log the event
    logger.logEvent("LED", "Starting LED test");

    LightController blueLED(BLUE_LED_PIN, dailyOnTime, dailyOffTime);
    LightController greenLED(GREEN_LED_PIN, dailyOnTime, dailyOffTime);


    // Control the lights based on the current time
    while (currentTime < dailyOffTime) {
        // Turn on the lights
        blueLED.turnOn();
        greenLED.turnOn();

        // Sleep for 10 seconds
        sleep(LOOP_COUNT);

        // Turn off the lights
        blueLED.turnOff();
        greenLED.turnOff();

        // Sleep for 10 seconds
        sleep(LOOP_COUNT);

        // Get the current time
        currentTime = time(NULL);
    }

    return 0;
}
