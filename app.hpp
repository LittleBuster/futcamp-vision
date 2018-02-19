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

#ifndef HOUSE_DEV_H
#define HOUSE_DEV_H

#include "deviceserver.hpp"
#include "threadmanager.hpp"
#include "log.hpp"
#include "locker.hpp"
#include "handlersmaker.hpp"
#include "configs.hpp"


class App
{
public:
    App(const shared_ptr<ILog> &log,
        const shared_ptr<IConfigs> &cfg,
        const shared_ptr<IHandlersMaker> &hmaker,
        const shared_ptr<IThreadManager> &tmanager,
        const shared_ptr<IDeviceServer> &server,
        const shared_ptr<ILocker> &locker);

    /**
     * @brief Start device firmware
     *
     * @return Exit code
     */
    int start();

private:
    const shared_ptr<ILog> log_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<IHandlersMaker> hmaker_;
    const shared_ptr<IThreadManager> tmanager_;
    const shared_ptr<IDeviceServer> server_;
    const shared_ptr<ILocker> locker_;
};


#endif
