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

    // Create a logger
    Logger logger;

    // Log the event
    logger.logEvent("LED", "Starting LED test");

    // Set daily on/off day and time
    struct tm dailyOnTime;
    dailyOnTime.tm_hour = 23;
    dailyOnTime.tm_min = 55;
    dailyOnTime.tm_sec = 0;
    dailyOnTime.tm_year = 123;
    dailyOnTime.tm_mon = 11 - 1;
    dailyOnTime.tm_mday = 24;

    struct tm dailyOffTime;
    dailyOffTime.tm_hour = 00;
    dailyOffTime.tm_min = 05;
    dailyOffTime.tm_sec = 00;
    dailyOffTime.tm_year = 123;
    dailyOffTime.tm_mon = 11 - 1;
    dailyOffTime.tm_mday = 25;

    // Log the setting of start time and end time and the times
    logger.logEvent("LED", "Setting start time and end time");

    time_t ontime  = mktime(&dailyOnTime);
    time_t offtime = mktime(&dailyOffTime);

    // Lof the conversion of the times to time_t
    logger.logEvent("LED", "Start time as time_t: " + std::to_string(ontime));
    logger.logEvent("LED", "End time as time_t: " + std::to_string(offtime));

    // output the on/off times
    std::cout << "On time: " << ctime(&ontime) << std::endl;
    std::cout << "Off time: " << ctime(&offtime) << std::endl;

    // Get the current time
    time_t currentTime = time(NULL);
    std::cout << "Current time: " << ctime(&currentTime) << std::endl;

    // Create the LED objects
    LightController blueLED(BLUE_LED_PIN, ontime, offtime);
    LightController greenLED(GREEN_LED_PIN, ontime, offtime);


    // Loop forever (or until Ctrl-C) and turn lights on/off depending on time
    while (true) {
        // Get the current time
        currentTime = time(NULL);
        std::cout << "Current time: " << ctime(&currentTime) << std::endl;

        // Log the current time
        logger.logEvent("LED", "Current time: " + std::string(ctime(&currentTime)));

        // output the on/off times
        std::cout << "On time: " << ctime(&ontime) << std::endl;
        std::cout << "Off time: " << ctime(&offtime) << std::endl;

        // Log the on/off times
        logger.logEvent("LED", "On time: " + std::string(ctime(&ontime)));
        logger.logEvent("LED", "Off time: " + std::string(ctime(&offtime)));

        // Output the logic test results
        std::cout << "Current time > ontime: " << (currentTime > ontime) << std::endl;
        std::cout << "Current time < offtime: " << (currentTime < offtime) << std::endl;

                // Log the logic test results
        logger.logEvent("LED", "Current time > ontime: " + std::to_string(currentTime > ontime));
        logger.logEvent("LED", "Current time < offtime: " + std::to_string(currentTime < offtime));

        // Check if the current time is between the on/off times
        if (currentTime > ontime && currentTime < offtime) {
            // Turn the lights on
            blueLED.turnOn();
            greenLED.turnOn();

            // Log the event
            logger.logEvent("LED", "Turning lights on");

        } else {
            // Turn the lights off
            blueLED.turnOff();
            greenLED.turnOff();
        }

        // Sleep for 1 second
        sleep(1);
    }

    return 0;
}
