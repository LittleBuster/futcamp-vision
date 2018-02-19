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

#include "locker.hpp"


void Locker::addModule(const string &module)
{
    locks_.insert(make_pair(module, make_shared<mutex>()));
}

void Locker::lockModule(const string &module)
{
    locks_[module]->lock();
}

void Locker::unlockModule(const string &module)
{
    locks_[module]->unlock();
}
