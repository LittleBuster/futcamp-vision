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

#ifndef IHANDLER_HPP
#define IHANDLER_HPP

#include "httpclient.hpp"

#include <string>

using namespace std;


class IHandler
{
public:
    virtual bool process(const shared_ptr<IHttpClient> &client, const string &request) = 0;
};


#endif
