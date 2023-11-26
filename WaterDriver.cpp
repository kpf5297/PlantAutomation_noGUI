/*
    To compile:
        g++ -I/home/kpf5297/Code/ManualControl WaterDriver.cpp WaterPump.cpp -o WD -lgpiod -lrt -lpthread

        g++ -I/home/kpf5297/Code/ManualControl WaterPump.cpp WaterDriver.cpp -o WaterDriver -lgpiod -lrt -lpthread

*/
#include "WaterPump.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // Create a WaterPump object with GPIO pin 17, ignore time of 5 seconds, and pump time of 10 seconds
    WaterPump myWaterPump(17, 5, 10);

    // Activate the water pump
    std::cout << "Activating water pump..." << std::endl;
    myWaterPump.activate();

    // Sleep for a while to simulate the pump running
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // output the last activation time (returns a std::tm struct)
    std::cout << "Last activation time: " << myWaterPump.getLastActivation().tm_hour << ":" << myWaterPump.getLastActivation().tm_min << ":" << myWaterPump.getLastActivation().tm_sec << std::endl;

    // Deactivate the water pump
    std::cout << "Deactivating water pump..." << std::endl;
    myWaterPump.deactivate();

    // Sleep for a while to simulate the pump not running
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // output the last activation time (returns a std::tm struct)
    std::cout << "Last activation time: " << myWaterPump.getLastActivation().tm_hour << ":" << myWaterPump.getLastActivation().tm_min << ":" << myWaterPump.getLastActivation().tm_sec << std::endl;


    // Tell user now testing the getStatus() function
    std::cout << "Now testing the getStatus() function..." << std::endl;

    // Toggle the water pump
    std::cout << "Toggling water pump..." << std::endl;
    myWaterPump.toggle();

    // output the last activation time (returns a std::tm struct)
    std::cout << "Last activation time: " << myWaterPump.getLastActivation().tm_hour << ":" << myWaterPump.getLastActivation().tm_min << ":" << myWaterPump.getLastActivation().tm_sec << std::endl;


    // Check the status of the water pump
    if (myWaterPump.getStatus()) {
        std::cout << "Water pump is currently running." << std::endl;
    } else {
        std::cout << "Water pump is currently not running." << std::endl;
    }

    // Sleep for a while to simulate the pump running
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Toggle the water pump
    std::cout << "Toggling water pump..." << std::endl;
    myWaterPump.toggle();

    // Check the status of the water pump
    if (myWaterPump.getStatus()) {
        std::cout << "Water pump is currently running." << std::endl;
    } else {
        std::cout << "Water pump is currently not running." << std::endl;

    // output the last activation time (returns a std::tm struct)
    std::cout << "Last activation time: " << myWaterPump.getLastActivation().tm_hour << ":" << myWaterPump.getLastActivation().tm_min << ":" << myWaterPump.getLastActivation().tm_sec << std::endl;

    }

    // Sleep for a while to simulate the pump not running
    std::this_thread::sleep_for(std::chrono::seconds(5));



    // Set a new activation duration
    myWaterPump.setActivationDuration(15);

    // Get the activation duration
    std::cout << "New activation duration: " << myWaterPump.getActivationDuration() << " seconds." << std::endl;

    return 0;
}
