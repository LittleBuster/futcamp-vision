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

#include "camhandler.hpp"
#include "utils.hpp"
#include "pageparser.hpp"
#include "path.hpp"

#include <vector>


CameraHandler::CameraHandler(const shared_ptr<ILog> &log,
                             const shared_ptr<ICamera> &cam):
                             log_(std::move(log)),
                             cam_(std::move(cam))
{
}

bool CameraHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    vector<string> parts;
    unsigned cam;
    auto parser = make_shared<PageParser>();

    if (!splitString(parts, request, "="))
        return false;
    if (parts[0] != "dev")
        return false;

    cam = stoi(parts[1]);

    if (!cam_->open(cam)) {
        if (!parser->loadFromFile(Path::getInstance().getPath("ErrorPage"))) {
            log_->error("Load 403.html failed: " + parser->getLastError(), "CAMERA");
            return false;
        }
        if (!client->sendTextResponse(parser->getFullPage(), HTTP_FORBIDDEN))
            return false;
        return true;
    }

    if (!cam_->getPhoto()) {
        cam_->close();
        if (!parser->loadFromFile(Path::getInstance().getPath("ErrorPage"))) {
            log_->error("Load 403.html failed: " + parser->getLastError(), "CAMERA");
            return false;
        }
        if (!client->sendTextResponse(parser->getFullPage(), HTTP_FORBIDDEN))
            return false;
        return true;
    }

    cam_->savePhoto("/tmp/photo" + to_string(cam) + ".jpg");
    cam_->close();

    if (!client->sendImageResponse("/tmp/photo" + to_string(cam) + ".jpg"))
        return false;

    return true;
}
