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

#ifndef HANDLERS_MAKER_HPP
#define HANDLERS_MAKER_HPP

#include "log.hpp"
#include "ihandler.hpp"
#include "camera.hpp"
#include "system.hpp"
#include "configs.hpp"

#include <map>


class IHandlersMaker
{
public:
    virtual shared_ptr<IHandler> makeHandler(const string &name) = 0;
};


class HandlersMaker: public IHandlersMaker
{
public:
    HandlersMaker(const shared_ptr<ILog> &log,
                  const shared_ptr<IConfigs> &cfg,
                  const shared_ptr<ICamera> &cam,
                  const shared_ptr<ISystem> &sys);

    /**
     * @brief Make new handler
     *
     * @param name Name of handler
     *
     * @return Handler's pointer
     */
    shared_ptr<IHandler> makeHandler(const string &name);

private:
    const shared_ptr<ILog> log_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<ICamera> cam_;
    const shared_ptr<ISystem> sys_;
};


#endif
