/*    
    Filename: Relay.h

    Purpose: Control 8 solid state relays using a Raspberry Pi 4B
    
    Using:  Raspberry Pi 4B (3.3v)
            SaintSmart 8 Channel Solid State Relay Module (Active High)
    
    Author:         Kevin Fox
    Date Created:   24 OCT 2023

*/

#ifndef RELAY_H
#define RELAY_H

#include <iostream>
#include <unistd.h>
#include <gpiod.h>

class Relay {
    
friend class WaterPump;

    private:
        gpiod_chip *chip;
        gpiod_line *line;
        bool state;
        int pinNum;
    public:
        Relay(int pinNumber);
        ~Relay();
        void setState(bool state);
        int getState();
};

#endif