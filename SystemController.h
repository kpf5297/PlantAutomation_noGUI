#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "SoilSensor.h"
#include "LightController.h"
#include "WaterPump.h"

class SystemController {
public:
    SystemController(uint8_t soilSensorAddress, ADS1115::Mux soilSensorMux,
                     int lightControllerPin, time_t lightOnTime, time_t lightOffTime,
                     int waterPumpPin, int pumpIgnoreTime, int pumpDuration);
   