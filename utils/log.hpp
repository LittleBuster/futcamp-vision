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

#ifndef LOG_HPP
#define LOG_HPP

#include "locker.hpp"

#include <string>
#include <memory>

using namespace std;


class ILog
{
public:
    virtual void setLogFile(const string &filepath) = 0;
    virtual void error(const string &msg, const string &module) const = 0;
    virtual void info(const string &msg, const string &module) const = 0;
    virtual void warning(const string &msg, const string &module) const = 0;
};


/**
 * @brief The Log class
 *
 * Show and save log messages
 */
class Log: public ILog
{
public:
    explicit Log(const shared_ptr<ILocker> &locker);

    /**
     * @brief Setup path to log file
     *
     * @param filepath System path
     */
    inline void setLogFile(const string &filepath) { logPath_ = filepath; }

    /**
     * @brief Log error message
     *
     * @param msg incomming message
     * @param module program module whence message
     */
    void error(const string &msg, const string &module) const;

    /**
     * @brief Log information message
     *
     * @param msg incomming message
     * @param module program module whence message
     */
    void info(const string &msg, const string &module) const;

    /**
     * @brief Log warning message
     *
     * @param msg incomming message
     * @param module program module whence message
     */
    void warning(const string &msg, const string &module) const;

private:
    const shared_ptr<ILocker> locker_;

    string logPath_;

    /**
     * @breif Create log string and writing in file
     *
     * @param msg Logging message
     * @param type Log message type
     */
    void saveLogMsg(const string &msg, const string &module, unsigned type) const;
};


#endif
