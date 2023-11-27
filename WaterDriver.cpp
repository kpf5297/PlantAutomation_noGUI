/*
    To compile:
        g++ -I/home/kpf5297/Code/ManualControl WaterDriver.cpp WaterPump.cpp -o WD -lgpiod -lrt -lpthread

        g++ -I/home/kpf5297/Code/ManualControl WaterPump.cpp WaterDriver.cpp -o WaterDriver -lgpiod -lrt -lpthread

*/
#include "WaterPump.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

