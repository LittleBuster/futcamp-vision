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

#ifndef THREAD_MANAGER_HPP
#define THREAD_MANAGER_HPP

#include "imodule.hpp"

#include <thread>
#include <vector>
#include <memory>

using namespace std;


class IThreadManager
{
public:
    virtual void addModule(const shared_ptr<IModule> &module) = 0;
    virtual void startAll() = 0;
};


class ThreadManager: public IThreadManager
{
public:
    /**
     * @brief Add new app module
     *
     * @param module New module
     */
    void addModule(const shared_ptr<IModule> &module);

    /**
     * @brief Start all threads
     */
    void startAll();

private:
    vector<shared_ptr<IModule>> modules_;
    vector<shared_ptr<thread>> threads_;

    /**
     * @brief Start module in other thread
     *
     * @param mod App module
     */
    void startThread(const shared_ptr<IModule> &mod);
};


#endif
