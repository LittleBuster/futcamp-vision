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

#include "handlersmaker.hpp"
#include "notfoundhandler.hpp"
#include "errhandler.hpp"
#include "indexhandler.hpp"
#include "syshandler.hpp"
#include "camhandler.hpp"
#include "photohandler.hpp"
#include "fileshandler.hpp"


HandlersMaker::HandlersMaker(const shared_ptr<ILog> &log,
                             const shared_ptr<IConfigs> &cfg,
                             const shared_ptr<ICamera> &cam,
                             const shared_ptr<ISystem> &sys):
                             log_(std::move(log)),
                             cfg_(std::move(cfg)),
                             cam_(std::move(cam)),
                             sys_(std::move(sys))
{
}

shared_ptr<IHandler> HandlersMaker::makeHandler(const string &name)
{
    if (name == "/404")
        return make_shared<NotFoundHandler>(log_);
    if (name == "/403")
        return make_shared<ErrorHandler>(log_);
    if (name == "/")
        return make_shared<IndexHandler>(log_, cam_, sys_);
    if (name == "/sys")
        return make_shared<SystemHandler>(log_, sys_);
    if (name == "/cam")
        return make_shared<CameraHandler>(log_, cam_);
    if (name == "/photo")
        return make_shared<PhotoHandler>(log_, cfg_, cam_);
    if (name == "/files")
        return make_shared<FilesHandler>(log_, cfg_);

    return nullptr;
}
