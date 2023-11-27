// SystemController.cpp
#include "SystemController.h"

SystemController::SystemController(uint8_t soilSensorAddress, ADS1115::Mux soilSensorMux,
                                   int lightControllerPin, time_t lightOnTime, time_t lightOffTime
                                   int waterPumpPin, int pumpIgnoreTime, int pumpDuration) :
                                   soilSensor(soilSensorAddress, soilSensorMux),
                                   lightController(lightControllerPin, lightOnTime, lightOffTime),
                                   waterPump(waterPumpPin, pumpIgnoreTime, pumpDuration) {
    this->soilMoistureThreshold = 0.5;
    this->lightOnTime = lightOnTime;
    this->lightOffTime = lightOffTime;
    this->pumpDuration = pumpDuration;
    this->pumpIgnoreTime = pumpIgnoreTime;
}

SystemController::~SystemController() {
    // Nothing to do here
}

double SystemController::readSoilMoisture() {
    return soilSensor.readSoilMoisture();
}

bool SystemController::calibrateSoilSensor() {
    return soilSensor.calibrate();
}

void SystemController::controlLight(std::tm currentTime) {
    // Check if current time is in range
    if (isTimeInRange(currentTime, lightOnTime, lightOffTime)) {
        lightController.turnOn();
    } else {
        lightController.turnOff();
    }
}

void SystemController::controlWaterPump(std::tm currentTime) {
    // Check if current time is in range
    if (isTimeInRange(currentTime, waterPumpOnTime, waterPumpOffTime)) {
        waterPump.activate();
    } else {
        waterPump.deactivate();
    }
}

bool SystemController::isTimeInRange(std::tm currentTime, std::tm startTime, std::tm endTime) {
    // Check if current time is in range
    if (currentTime.tm_hour >= startTime.tm_hour && currentTime.tm_hour <= endTime.tm_hour) {
        if (currentTime.tm_hour == startTime.tm_hour) {
            if (currentTime.tm_min >= startTime.tm_min) {
                return true;
            } else {
                return false;
            }
        } else if (currentTime.tm_hour == endTime.tm_hour) {
            if (currentTime.tm_min <= endTime.tm_min) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void SystemController::setSoilMoistureThreshold(double threshold) {
    this->soilMoistureThreshold = threshold;
}

double SystemController::getSoilMoistureThreshold() {
    return soilMoistureThreshold;
}

void SystemController::setLightOnTime(std::tm lightOnTime) {
    this->lightOnTime = lightOnTime;
}

void SystemController::setLightOffTime(std::tm lightOffTime) {
    this->lightOffTime = lightOffTime;
}

time_t SystemController::getLightOnTime() {
    return lightOnTime;
}

time_t SystemController::getLightOffTime() {
    return lightOffTime;
}

void SystemController::setWaterPumpOnTime(std::tm waterPumpOnTime) {
    this->waterPumpOnTime = waterPumpOnTime;
}

void SystemController::setWaterPumpOffTime(std::tm waterPumpOffTime) {
    this->waterPumpOffTime = waterPumpOffTime;
}

void SystemController::setPumpIgnoreTime(std::tm pumpIgnoreTime) {
    this->pumpIgnoreTime = pumpIgnoreTime;
}

void SystemController::setPumpDuration(int pumpDuration) {
    this->pumpDuration = pumpDuration;
}

