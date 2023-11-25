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
    struct tm *onTime = localtime(&dailyOnTime);
    // onTime->tm_mday = 25;
    // onTime->tm_mon = 11 - 1;
    // onTime->tm_year = 2023 - 1900;
    onTime->tm_hour = 03;
    onTime->tm_min = 58;
    onTime->tm_sec = 0;
    dailyOnTime = mktime(onTime);

    // Output the daily on time
    std::cout << "Daily on time: " << ctime(&dailyOnTime) << std::endl;
    

    time_t dailyOffTime = time(NULL);
    struct tm *offTime = localtime(&dailyOffTime);
    // offTime->tm_mday = 25;
    // offTime->tm_mon = 11 - 1;
    // offTime->tm_year = 2023 - 1900;
    offTime->tm_hour = 03;
    offTime->tm_min = 58;
    offTime->tm_sec = 30;
    dailyOffTime = mktime(offTime);

    // Output the daily off time
    std::cout << "Daily off time: " << ctime(&dailyOffTime) << std::endl;

    time_t currentTime = time(NULL);

    // Output the current time
    std::cout << "Current time: " << ctime(&currentTime) << std::endl;

    // Create a logger
    Logger logger;

    // Log the event
    logger.logEvent("LED", "Starting LED test");

    LightController blueLED(BLUE_LED_PIN, dailyOnTime, dailyOffTime);
    LightController greenLED(GREEN_LED_PIN, dailyOnTime, dailyOffTime);

    // In an infinte while loop, turn on/off the lights based on the current time
    while (true) {
        currentTime = time(NULL);

        // Output the current time
        std::cout << "Current time: " << ctime(&currentTime) << std::endl;

        // Output the daily on time
        std::cout << "Daily on time: " << ctime(&dailyOnTime) << std::endl;

        // Output the daily off time
        std::cout << "Daily off time: " << ctime(&dailyOffTime) << std::endl;

        // Output the logic for turning on/off the lights
        std::cout << "Current time > dailyOnTime: " << (currentTime > dailyOnTime) << std::endl;

        std::cout << "Current time < dailyOffTime: " << (currentTime < dailyOffTime) << std::endl;

        if (currentTime > dailyOnTime && currentTime < dailyOffTime) {
            blueLED.turnOn();
            greenLED.turnOn();
        } else {
            blueLED.turnOff();
            greenLED.turnOff();
        }
        sleep(1);

        if (currentTime > dailyOffTime) {
            break;
        }
    }


    return 0;
}
