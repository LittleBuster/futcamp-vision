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

#include "threadmanager.hpp"

#include <functional>


void ThreadManager::addModule(const shared_ptr<IModule> &module)
{
    modules_.push_back(module);
}

void ThreadManager::startAll()
{
    for (auto mod : modules_) {
        threads_.push_back(make_shared<thread>(bind(&ThreadManager::startThread, this, mod)));
    }
    for (auto th : threads_)
        th->join();
}

void ThreadManager::startThread(const shared_ptr<IModule> &mod)
{
    mod->start();
}
