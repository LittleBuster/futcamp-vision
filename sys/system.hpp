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

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <string>

using namespace std;


class ISystem
{
public:
    virtual void reboot() = 0;
    virtual void powerOff() = 0;
    virtual bool getCpuTemp(int &temp) = 0;
    virtual bool getRamSize(int &total, int &used) = 0;
    virtual bool getDiskSpace(string &total, string &used) = 0;
    virtual bool getUptime(string &uptime) = 0;
    virtual void switchPowerLed(bool state) = 0;
    virtual void switchStatusLed(bool state) = 0;
};


class System: public ISystem
{
public:
    /**
     * @brief Reboot the system
     */
    void reboot();

    /**
     * @brief Power off the system
     */
    void powerOff();

    /**
     * @brief Get CPU temperature
     *
     * @param[out] temp Temperarure
     *
     * @return true If readed
     * @return false If fail to read
     */
    bool getCpuTemp(int &temp);

    /**
     * @brief Get RAM total and used size
     *
     * @param total Total RAM memory
     * @param used Used RAM memory
     *
     * @return true If readed
     * @return false If fail to read
     */
    bool getRamSize(int &total, int &used);

    /**
     * @brief Get disk total and used space
     *
     * @param total Total disk space
     * @param used Used disk space
     *
     * @return true If readed
     * @return false If fail to read
     */
    bool getDiskSpace(string &total, string &used);

    /**
     * @brief Get system uptime
     *
     * @param uptime System uptime
     *
     * @return true If readed
     * @return false If fail to read
     */
    bool getUptime(string &uptime);

    /**
     * @brief Switching power onboard led
     *
     * @param state Led state
     */
    void switchPowerLed(bool state);

    /**
     * @brief Switching status led
     *
     * @param state Led state
     */
    void switchStatusLed(bool state);
};


#endif
