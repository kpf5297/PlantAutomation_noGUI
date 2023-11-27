#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include "SoilSensor.h"
#include "LightController.h"
#include "WaterPump.h"

class SystemController {
public:
    SystemController(uint8_t soilSensorAddress, ADS1115::Mux soilSensorMux,
                     int lightControllerPin, time_t lightOnTime, time_t lightOffTime
                     int waterPumpPin, int pumpIgnoreTime, int pumpDuration);
    ~SystemController();

    // Methods to interact with different components
    double readSoilMoisture();
    bool calibrateSoilSensor();
    void controlLight(std::tm currentTime);
    void controlWaterPump(std::tm currentTime);
    bool isTimeInRange(std::tm currentTime, std::tm startTime, std::tm endTime);
    void setSoilMoistureThreshold(double threshold);    // Set soil moisture threshold
    double getSoilMoistureThreshold();                  // Get soil moisture threshold
    void setLightOnTime(std::tm lightOnTime);           // Set light on time
    void setLightOffTime(std::tm lightOffTime);         // Set light off time
    time_t getLightOnTime();                            // Get light on time
    time_t getLightOffTime();                           // Get light off time
    void setWaterPumpOnTime(std::tm waterPumpOnTime);   // Set water pump on time
    void setWaterPumpOffTime(std::tm waterPumpOffTime); // Set water pump off time
    void setPumpIgnoreTime(std::tm pumpIgnoreTime);     // Set water pump ignore time
    void setPumpDuration(int pumpDuration);             // Set water pump activation duration

    
private:
    SoilSensor soilSensor;          // Soil sensor object
    double soilMoistureThreshold;   // Soil moisture threshold
    


    LightController lightController;    // Light controller object
    time_t currentTime;            // Current time for parmeters
    time_t lightOnTime;            // Time to turn on light after activation
    time_t lightOffTime;           // Time to turn off light after activation

    WaterPump waterPump;            // Water pump object
    int pumpDuration;               // Water pump activation duration
    std::tm waterPumpOnTime;        // Time to turn on water pump after activation
    std::tm waterPumpOffTime;       // Time to turn off water pump after activation
    std::tm pumpIgnoreTime;         // Time to ignore water pump activation after last activation

};

#endif // SYSTEM_CONTROLLER_H
