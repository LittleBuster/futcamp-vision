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

#include "app.hpp"
#include "threadmanager.hpp"
#include "log.hpp"
#include "locker.hpp"
#include "deviceserver.hpp"
#include "handlersmaker.hpp"
#include "camera.hpp"
#include "system.hpp"
#include "configs.hpp"


int main(void)
{
    /*auto locker = make_shared<Locker>();
    auto tmanager = make_shared<ThreadManager>();
    auto cam = make_shared<Camera>();
    auto sys = make_shared<System>();
    auto cfg = make_shared<Configs>();
    auto log = make_shared<Log>(locker);
    auto server = make_shared<DeviceServer>(log);
    auto hmaker = make_shared<HandlersMaker>(log, cfg, cam, sys);
    auto app = make_shared<App>(log, cfg, hmaker, tmanager, server, locker);

    return app->start();*/


}
