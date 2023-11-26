// SoilSensor.cpp:
#include "SoilSensor.h"

#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <chrono>
#include <thread>


SoilSensor::SoilSensor(uint8_t address, ADS1115::Mux muxSelect) : ads1115(address, muxSelect) {
    // Set default values
    moisture = 0.0;
    calWetValue = CAL_WET_DEFAULT;
    calDryValue = CAL_DRY_DEFAULT;
}

SoilSensor::~SoilSensor() {
    // Nothing to destruct
}

double SoilSensor::readMoisture() {
    // Read the analog input
    int16_t rawValue = ads1115.read(ADS1115::Mux::AIN0_GND, ADS1115::Pga::FS_4_096V, ADS1115::Mode::SINGLE_SHOT, ADS1115::DataRate::SPS_128);

    // Print the raw value
    std::cout << "Raw Value: " << rawValue << std::endl;

    // Print the wet and dry calibration values
    std::cout << "Wet Value: " << calWetValue << std::endl;
    std::cout << "Dry Value: " << calDryValue << std::endl;
    

    // Map the voltage to a moisture value
    moisture = map(rawValue, calDryValue, calWetValue, 0.0, 100.0);

    // Constrain the moisture value to 0-100%
    moisture = constrain(moisture, 0.0, 100.0);

    return moisture;
}

bool SoilSensor::calibrate() {
    // Tell user to place sensor in air
    std::cout << "Place sensor in air and press ENTER to continue..." << std::endl;
    std::cin.ignore();

    // Read the analog input
    int16_t rawValue = ads1115.read(ADS1115::Mux::AIN0_GND, ADS1115::Pga::FS_4_096V, ADS1115::Mode::SINGLE_SHOT, ADS1115::DataRate::SPS_128);

    // Set the dry calibration value
    calDryValue = rawValue;

    // Tell user to place sensor in water
    std::cout << "Place sensor in water and press ENTER to continue..." << std::endl;
    std::cin.ignore();

    // Read the analog input
    rawValue = ads1115.read(ADS1115::Mux::AIN0_GND, ADS1115::Pga::FS_4_096V, ADS1115::Mode::SINGLE_SHOT, ADS1115::DataRate::SPS_128);

    // Set the wet calibration value
    calWetValue = rawValue;

    return true;
}

void SoilSensor::setWetCalValue(int16_t wetValue) {
    calWetValue = wetValue;
}

void SoilSensor::setDryCalValue(int16_t dryValue) {
    calDryValue = dryValue;
}

int16_t SoilSensor::getWetCalValue() {
    return calWetValue;
}

int16_t SoilSensor::getDryCalValue() {
    return calDryValue;
}

double SoilSensor::map(double x, double in_min, double in_max, double out_min, double out_max) {
    // Map the input range to the output range
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double SoilSensor::constrain(double x, double min, double max) {
    // Constrain the input value to the min-max range
    if (x < min) {
        return min;
    } else if (x > max) {
        return max;
    } else {
        return x;
    }
}


