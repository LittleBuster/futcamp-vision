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

#include "notfoundhandler.hpp"
#include "pageparser.hpp"
#include "path.hpp"


NotFoundHandler::NotFoundHandler(const shared_ptr<ILog> &log):
                                 log_(std::move(log))
{
}

bool NotFoundHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    (void)request;
    auto parser = make_shared<PageParser>();

    if (!parser->loadFromFile(Path::getInstance().getPath("NotFoundPage"))) {
        log_->error("Load 404.html failed: " + parser->getLastError(), "NOT_FOUND");
        return false;
    }

    if (!client->sendTextResponse(parser->getFullPage(), HTTP_NOT_FOUND))
        return false;

    return true;
}
