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

#ifndef CONFIGS_HPP
#define CONFIGS_HPP

#include <string>

using namespace std;


typedef struct {
    unsigned port;
    unsigned users;
    bool threaded;
} ServerCfg;

typedef struct {
    unsigned width;
    unsigned height;
} PhotoCfg;

typedef struct {
    string files;
    string templates;
} PathCfg;


class IConfigs
{
public:
    virtual bool loadFromFile(const string &filename) = 0;
    virtual const ServerCfg &getServer() const = 0;
    virtual const PhotoCfg &getPhoto() const = 0;
    virtual const PathCfg &getPath() const = 0;
    virtual const string &getLastError() const = 0;
};


class Configs: public IConfigs
{
public:
    /**
     * @brief Loading configs from file
     *
     * @param filename Path to confgigs file
     *
     * @return true If configs was loaded
     * @return false If fail to load configs
     */
    bool loadFromFile(const string &filename);

    /**
     * @brief Get server configs
     *
     * @return Server configs
     */
    inline const ServerCfg &getServer() const { return sc_; }

    /**
     * @brief Get photo configs
     *
     * @return Server configs
     */
    inline const PhotoCfg &getPhoto() const { return pc_; }

    /**
     * @brief Get files configs
     *
     * @return Server configs
     */
    inline const PathCfg &getPath() const { return ptc_; }

    /**
     * @brief Get last error of loading
     *
     * @return Last error string
     */
    inline const string &getLastError() const { return error_; }

private:
    ServerCfg sc_;
    PhotoCfg pc_;
    PathCfg ptc_;
    string error_;
};


#endif
