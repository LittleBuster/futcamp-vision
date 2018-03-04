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

#ifndef FILES_HANDLER_HPP
#define FILES_HANDLER_HPP

#include "ihandler.hpp"
#include "httpclient.hpp"
#include "log.hpp"
#include "configs.hpp"


class FilesHandler: public IHandler
{
public:
    FilesHandler(const shared_ptr<ILog> &log,
                 const shared_ptr<IConfigs> &cfg);

    /**
     * @brief Process request
     *
     * @param client Http client
     * @param request Http request
     *
     * @return true If processed
     * @return false if fail to process request
     */
    bool process(const shared_ptr<IHttpClient> &client, const string &request);

private:
    const shared_ptr<ILog> log_;
    const shared_ptr<IConfigs> cfg_;
};


#endif
