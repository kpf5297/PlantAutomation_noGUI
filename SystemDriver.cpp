// SystemDriver.cpp
/*
        g++ -I/home/kpf5297/Code/ManualControl SystemDriver.cpp SystemController.cpp Logging.cpp LightController.cpp SoilSensor.cpp WaterPump.cpp ADS1115.cpp -o SystemDriver -lgpiod -lrt -lpthread

*/
#include "SystemController.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>


int16_t ADS1115_ADDRESS = 0x48;
int LIGHT_PIN = 27;
int PUMP_PIN = 17;
int PUMP_WAIT_TIME = 10;
int PUMP_DURATION = 5;
ADS1115::Mux MUX_SELECT = ADS1115::Mux::AIN0_GND;

int main() {

    // Set daily on time for the current date
    time_t dailyOnTime = time(NULL);
    struct tm *onTime = localtime(&dailyOnTime);
    /*      Enable these if you want to also control a specific date      */
    // onTime->tm_mday = 25;
    // onTime->tm_mon = 11 - 1;
    // onTime->tm_year = 2023 - 1900;
    onTime->tm_hour = 15;
    onTime->tm_min = 47;
    onTime->tm_sec = 0;
    dailyOnTime = mktime(onTime);

    // Set daily off time for the current date
    time_t dailyOffTime = time(NULL);
    struct tm *offTime = localtime(&dailyOffTime);
    /*      Enable these if you want to also control a specific date      */
    // offTime->tm_mday = 25;
    // offTime->tm_mon = 11 - 1;
    // offTime->tm_year = 2023 - 1900;
    offTime->tm_hour = 15;
    offTime->tm_min = 47;
    offTime->tm_sec = 30;
    dailyOffTime = mktime(offTime);

    time_t currentTime = time(NULL);

    // Initialize system controller
    SystemController systemController(ADS1115_ADDRESS, MUX_SELECT, LIGHT_PIN, dailyOnTime, dailyOffTime, PUMP_PIN, PUMP_WAIT_TIME, PUMP_DURATION);

    // Calibrate the soil sensor
    // systemController.calibrateSoilSensor();

    // Set the soil moisture threshold
    systemController.setSoilMoistureThreshold(0.5);

    // Loop forever
    while (true) {

        // Update the current time
        currentTime = time(NULL);

        // cout current time
        std::cout << "Current time: " << ctime(&currentTime) << std::endl;

        // cout daily on time
        std::cout << "Daily on time: " << ctime(&dailyOnTime) << std::endl;

        // cout daily off time
        std::cout << "Daily off time: " << ctime(&dailyOffTime) << std::endl;

        // Activate the garden components
        systemController.controlLight(currentTime);

        // Wait 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Break once the current time is past the daily off time
        if (currentTime > dailyOffTime) {
            break;
        }

    }

    return 0;
}
