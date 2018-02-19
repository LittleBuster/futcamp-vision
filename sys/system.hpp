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


class ISystem
{
public:
    virtual void reboot() = 0;
    virtual void powerOff() = 0;
    virtual bool getCpuTemp(int &temp) = 0;
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
