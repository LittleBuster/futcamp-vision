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

#ifndef LOCKER_HPP
#define LOCKER_HPP

#include <map>
#include <mutex>
#include <memory>

using namespace std;


class ILocker
{
public:
    virtual void addModule(const string &module) = 0;
    virtual void lockModule(const string &module) = 0;
    virtual void unlockModule(const string &module) = 0;
};


class Locker: public ILocker
{
public:
    /**
     * @brief Add new mutex with name
     *
     * @param module Program module
     */
    void addModule(const string &module);

    /**
     * @brief Lock mutex with name
     *
     * @param module Program module
     */
    void lockModule(const string &module);

    /**
     * @brief Unlock mutex with name
     *
     * @param module Program module
     */
    void unlockModule(const string &module);

private:
    map<string, shared_ptr<mutex>> locks_;
};


#endif
