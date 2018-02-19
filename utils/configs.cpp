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

#include "configs.hpp"
#include "cfgreader.hpp"


bool Configs::loadFromFile(const string &filename)
{
    CfgReader reader(filename);
    if (!reader.isOpen()) {
        error_ = "File not found";
        return false;
    }

    if (!reader.readInt("Server", "Port", (int &)sc_.port)) {
        error_ = "Fail to read server port";
        return false;
    }
    if (!reader.readInt("Server", "Users", (int &)sc_.users)) {
        error_ = "Fail to read server max users";
        return false;
    }
    if (!reader.readBool("Server", "Multithread", sc_.threaded)) {
        error_ = "Fail to read server multithreaded mode";
        return false;
    }

    if (!reader.readInt("Photo", "Width", (int &)pc_.width)) {
        error_ = "Fail to read photo width";
        return false;
    }
    if (!reader.readInt("Photo", "Height", (int &)pc_.height)) {
        error_ = "Fail to read photo height";
        return false;
    }
    return true;
}
