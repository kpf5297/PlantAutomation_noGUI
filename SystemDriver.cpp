// SystemDriver.cpp
/*
        g++ -I/home/kpf5297/Code/ManualControl SystemDriver.cpp SystemController.cpp Logging.cpp LightController.cpp SoilSensor.cpp WaterPump.cpp ADS1115.cpp -o SystemDriver -lgpiod -lrt -lpthread

*/
#include "SystemController.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

int main() {

    // Set daily on time for the current date
    time_t dailyOnTime = time(NULL);
    struct tm *onTime = localtime(&dailyOnTime);
    /*      Enable these if you want to also control a specific date      */
    // onTime->tm_mday = 25;
    // onTime->tm_mon = 11 - 1;
    // onTime->tm_year = 2023 - 1900;
    onTime->tm_hour = 03;
    onTime->tm_min = 29;
    onTime->tm_sec = 0;
    dailyOnTime = mktime(onTime);

    // Set daily off time for the current date
    time_t dailyOffTime = time(NULL);
    struct tm *offTime = localtime(&dailyOffTime);
    /*      Enable these if you want to also control a specific date      */
    // offTime->tm_mday = 25;
    // offTime->tm_mon = 11 - 1;
    // offTime->tm_year = 2023 - 1900;
    offTime->tm_hour = 03;
    offTime->tm_min = 29;
    offTime->tm_sec = 30;
    dailyOffTime = mktime(offTime);


    // Initialize system controller
    SystemController systemController(0x48, ADS1115::Mux::AIN0_GND, 17, *onTime, *offTime, 27, 1, 1);

    // Calibrate soil sensor
    systemController.calibrateSoilSensor();

    // Get current time
    time_t currentTime = time(NULL);

    // Set Soil moisture threshold
    systemController.setSoilMoistureThreshold(0.5);  

    // Get light on and off times
    time_t lightOnTime = systemController.getLightOnTime();
    time_t lightOffTime = systemController.getLightOffTime();

    // Run system controller
    while (true) {

        // Get current time
        currentTime = time(NULL);

        // Print current time
        std::cout << "Current time: " << ctime(&currentTime) << std::endl;

        // Read Soil moisture
        std::cout << "Soil moisture: " << systemController.readSoilMoisture() << std::endl;

        // Print soil moisture threshold
        std::cout << "Soil moisture threshold: " << systemController.getSoilMoistureThreshold() << std::endl;

        // Print light on and off times
        std::cout << "Light on time: " << ctime(&lightOnTime);
        std::cout << "Light off time: " << ctime(&lightOffTime);

        // Control light
        systemController.controlLight(*localtime(&currentTime));

        // Control water pump
        systemController.controlWaterPump(*localtime(&currentTime));

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
