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

#include <sstream>

#include "utils.hpp"


#define DATE_SIZE 21


bool splitString(vector<string> &out, const string &str, const string &sym)
{
    size_t pos;
    string token;
    string splStr(str);

    while ((pos = splStr.find(sym)) != string::npos) {
        token = splStr.substr(0, pos);
        out.push_back(token);
        splStr.erase(0, pos + sym.length());
    }
    token = splStr.substr(0, pos);
    if (token != "")
        out.push_back(token);

    if (out.size() < 2)
        return false;
    return true;
}

std::tuple<string, string> getCurDate()
{
    time_t now = time(0);
    struct tm ts;
    char buf[DATE_SIZE];
    char buf2[DATE_SIZE];

    ts = *localtime(&now);
    strftime(buf, DATE_SIZE - 1, "%F", &ts);
    strftime(buf2, DATE_SIZE - 1, "%T", &ts);

    return make_tuple(string(buf), string(buf2));
}
