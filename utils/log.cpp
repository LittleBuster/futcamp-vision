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

#include <iostream>
#include <fstream>

#include "log.hpp"
#include "utils.hpp"

using namespace std;


enum LogType {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO
};


Log::Log(const shared_ptr<ILocker> &locker):
         locker_(std::move(locker)),
         logPath_("")
{
}

void Log::error(const string &msg, const string &module) const
{
    locker_->lockModule("LOG");
    saveLogMsg(msg, module, LOG_ERROR);
    locker_->unlockModule("LOG");
}

void Log::info(const string &msg, const string &module) const
{
    locker_->lockModule("LOG");
    saveLogMsg(msg, module, LOG_INFO);
    locker_->unlockModule("LOG");
}

void Log::warning(const string &msg, const string &module) const
{
    locker_->lockModule("LOG");
    saveLogMsg(msg, module, LOG_WARNING);
    locker_->unlockModule("LOG");
}

void Log::saveLogMsg(const string &msg, const string &module, unsigned type) const
{
    string out;
    ofstream log;

    auto dt = getCurDate();
    out = "[" + get<0>(dt) + "][" + get<1>(dt) + "][" + module + "][";

    switch (type) {
        case LOG_ERROR: {
            out += "ERROR] ";
            break;
        }
        case LOG_WARNING: {
            out += "WARNING] ";
            break;
        }
        case LOG_INFO: {
            out += "INFO] ";
            break;
        }
    }
    out += msg;
    cout << out << endl;

    if (logPath_ == "")
        return;

    log.open(logPath_, ios::out | ios::ate | ios::app);
    if (!log.is_open()) {
        cout << "[ERR] Fail writing to log file." << endl;
        return;
    }
    log << out << "\n";
    log.close();
}
