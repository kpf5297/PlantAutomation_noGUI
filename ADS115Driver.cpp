/*
    g++ ADS115Driver.cpp ADS1115.cpp -o A2DDriver


*/

#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include <thread>

#include "ADS1115.h"

int main() {

    // Create an ADS1115 ADC (16-bit) instance
    ADS1115 adc(0x48, ADS1115::Mux::AIN0_GND);
    ADS1115 adc1(0x48, ADS1115::Mux::AIN1_GND);
    ADS1115 adc2(0x48, ADS1115::Mux::AIN2_GND);
    ADS1115 adc3(0x48, ADS1115::Mux::AIN3_GND);

    // Read the analog input 100 times
    for (int i = 0; i < 100; i++) {
        std::cout << "AIN0: " << std::dec << adc.read0() << std::endl;
        std::cout << "AIN1: " << std::dec << adc1.read1() << std::endl;
        std::cout << "AIN2: " << std::dec << adc2.read2() << std::endl;
        std::cout << "AIN3: " << std::dec << adc3.read3() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}