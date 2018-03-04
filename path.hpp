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

#ifndef PATH_HPP
#define PATH_HPP

#include <memory>
#include <unordered_map>
#include <string>

using namespace std;


class Path
{
public:
    /**
     * @brief Get instanse of path
     *
     * @return Path
     */
    static Path &getInstance();

    /**
     * @brief Get path by name
     *
     * @param name Name of path
     *
     * @return Path string
     */
    const string &getPath(const string &name);

    /**
     * @brief Add new path
     *
     * @param name Name of file
     * @param path Path to file
     */
    void addPath(const string &name, const string &path);

    /**
     * @brief Removed contructors
     */
    Path(Path const&) = delete;
    Path(Path&&) = delete;
    Path& operator=(Path const&) = delete;
    Path& operator=(Path &&) = delete;

protected:
    Path();
    ~Path();

private:
    unordered_map<string, string> paths_;
};


#endif
