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
#include "utils.hpp"

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

    system("cat /sys/class/thermal/thermal_zone0/temp > /tmp/temp");

    ifstream file("/tmp/temp");
    if (!file.is_open())
        return false;

    file.getline(buf, 255);
    temp = stoi(string(buf));

    file.close();
    return true;
#elif
    return false;
#endif
}

bool System::getRamSize(int &total, int &used)
{
#ifdef ORAGNE_PI_PLATFORM
    string line;

    system("free -m > /tmp/mem");

    ifstream file("/tmp/mem");
    if (!file.is_open())
        return false;

    for (unsigned i = 0; i < 8; i++)
        file >> line;

    total = stoi(line);

    for (unsigned i = 0; i < 8; i++)
        file >> line;

    used = stoi(line);

    file.close();
    return true;
#elif
    return false;
#endif
}

bool System::getDiskSpace(string &total, string &used)
{
#ifdef ORAGNE_PI_PLATFORM
    string line;

    system("df -ah > /tmp/disk");

    ifstream file("/tmp/disk");
    if (!file.is_open())
        return false;

    while (!file.eof()) {
        file >> line;
        if (line == "/dev/mmcblk0p1")
            break;
    }

    file >> total;
    file >> used;

    file.close();
    return true;
#elif
    return false;
#endif
}

bool System::getUptime(string &uptime)
{
#ifdef ORAGNE_PI_PLATFORM
    string line;
    vector<string> parts, time;

    system("uptime > /tmp/up");

    ifstream file("/tmp/up");
    if (!file.is_open())
        return false;

    for (unsigned i = 0; i < 3; i++)
        file >> line;

    file.close();

    if (!splitString(parts, line, ","))
        return false;
    if (parts.size() == 0)
        return false;
    if (!splitString(time, parts[0], ":"))
        return false;
    if (time.size() < 2)
        return false;

    uptime = time[0] + "h" + time[1] + "m";

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
