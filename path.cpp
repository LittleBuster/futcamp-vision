/*****************************************************************************
 *
 * Future Camp Project
 *
 * Copyright (C) 2017-2018 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 *****************************************************************************/

#include "path.hpp"


Path &Path::getInstance()
{
    static Path path;
    return path;
}

const string &Path::getPath(const string &name)
{
    return paths_[name];
}

Path::Path()
{
    paths_.insert(make_pair("log", "/var/log/fcvision.log"));
    paths_.insert(make_pair("cfg", "/etc/fcvision.conf"));
    paths_.insert(make_pair("IndexPage", "/usr/share/fcvision/templates/index.html"));
}

Path::~Path()
{
}
