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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <tuple>
#include <map>

using namespace std;


/**
 * @brief Split string
 *
 * @param[out] out Out list with parts
 * @param[in] str Spliting string
 * @param[in] sym Delim symbol
 */
bool splitString(vector<string> &out, const string &str, const string &sym);

/**
 * @brief Get current date and time
 *
 * @return <0> Current date
 * @return <1> Current time
 */
tuple<string, string> getCurDate();


#endif
