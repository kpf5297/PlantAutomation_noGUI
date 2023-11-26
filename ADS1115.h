#ifndef ADS1115_H
#define ADS1115_H

#include <stdint.h>

class ADS1115 {

    friend class SoilMoistSensor;
    
public:
    enum class Mux : uint16_t {
        AIN0_AIN1 = 0x0000,         // Analog input AIN0 and AIN1 differential
        AIN0_AIN3 = 0x1000,         // Analog input AIN0 and AIN3 differential
        AIN1_AIN3 = 0x2000,         // Analog input AIN1 and AIN3 differential
        AIN2_AIN3 = 0x3000,         // Analog input AIN2 and AIN3 differential
        AIN0_GND = 0x4000,          // Analog input AIN0 and GND single-ended
        AIN1_GND = 0x5000,          // Analog input AIN1 and GND single-ended
        AIN2_GND = 0x6000,          // Analog input AIN2 and GND single-ended
        AIN3_GND = 0x7000           // Analog input AIN3 and GND single-ended
    };

    enum class Pga : uint16_t {
        FS_6_144V = 0x0000,         // +/-6.144V range = Gain 2/3
        FS_4_096V = 0x0200,         // +/-4.096V range = Gain 1
        FS_2_048V = 0x0400,         // +/-2.048V range = Gain 2     
        FS_1_024V = 0x0600,         // +/-1.024V range = Gain 4
        FS_0_512V = 0x0800,         // +/-0.512V range = Gain 8
        FS_0_256V = 0x0A00          // +/-0.256V range = Gain 16
    };

    enum class Mode : uint16_t {
        CONTINUOUS = 0x0000,        // Continuous conversion mode
        SINGLE_SHOT = 0x0100        // Power-down single-shot mode
    };

    enum class DataRate : uint16_t {
        SPS_8 = 0x0000,             // 8 samples per second
        SPS_16 = 0x0020,            // 16 samples per second
        SPS_32 = 0x0040,            // 32 samples per second
        SPS_64 = 0x0060,            // 64 samples per second
        SPS_128 = 0x0080,           // 128 samples per second (default)
        SPS_250 = 0x00A0,           // 250 samples per second
        SPS_475 = 0x00C0,           // 475 samples per second
        SPS_860 = 0x00E0            // 860 samples per second
    };

    ADS1115(uint8_t address, Mux muxSelect);
    ~ADS1115();

    int16_t read(Mux mux, Pga pga, Mode mode, DataRate dataRate);
    
    // Read for each analog input (single-ended, single-shot) using no parameters
    int16_t read0();
    int16_t read1();
    int16_t read2();
    int16_t read3();

private:
    uint8_t m_address;
    uint8_t m_buf[3];
    int m_fd;
    Mux mux;
    Pga pga;
    Mode mode;
    DataRate dataRate;
};

#endif // ADS1115_H

