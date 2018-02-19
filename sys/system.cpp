/*****************************************************************************
 *
 * Future Camp Project
 *
 * Copyright (C) 2017 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 *****************************************************************************/

#include "system.hpp"
#include "platform.hpp"

#include <stdlib.h>

#include <fstream>

using namespace std;


void System::reboot()
{
    system("reboot");
}

void System::powerOff()
{
    system("poweroff");
}

bool System::getCpuTemp(int &temp)
{
#ifdef ORAGNE_PI_PLATFORM
    char buf[256];

    system("cat /sys/class/thermal/thermal_zone0/temp >> /tmp/temp");

    ifstream file("/tmp/temp");
    if (!file.is_open())
        return false;

    file.getline(buf, 255);
    temp = stoi(string(buf)) / 1000;

    file.close();
    return true;
#elif
    return false;
#endif
}

void System::switchPowerLed(bool state)
{
#ifdef ORAGNE_PI_PLATFORM
    if (state)
        system("echo 1 > /sys/class/leds/orangepi:green:pwr/brightness");
    else
        system("echo 0 > /sys/class/leds/orangepi:green:pwr/brightness");
#endif
}

void System::switchStatusLed(bool state)
{
#ifdef ORAGNE_PI_PLATFORM
    if (state)
        system("echo 1 > /sys/class/leds/orangepi:red:status/brightness");
    else
        system("echo 0 > /sys/class/leds/orangepi:red:status/brightness");
#endif
}
