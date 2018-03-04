/*****************************************************************************
 *
 * Future Camp Project
 *
 * Copyright (C) 2018 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 *****************************************************************************/

#ifndef HANDLERS_HPP
#define HANDLERS_HPP

#include <string>

using namespace std;


#define HANDLERS_COUNT 7


static string httpHandlers[HANDLERS_COUNT] = {
    "/403",
    "/404",
    "/sys",
    "/cam",
    "/photo",
    "/files",
    "/"
};


#endif
