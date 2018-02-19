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

#include <vector>


CameraHandler::CameraHandler(const shared_ptr<ILog> &log,
                             const shared_ptr<ICamera> &cam):
                             log_(std::move(log)),
                             cam_(std::move(cam))
{
}

bool CameraHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    string body;
    vector<string> parts;
    unsigned cam;

    if (!splitString(parts, request, "="))
        return false;
    if (parts[0] != "dev")
        return false;

    cam = stoi(parts[1]);

    if (!cam_->open(cam)) {
        body = "<html><body><h1><font color=\"red\">Device not found</font></h1></body></html>";
        if (!client->sendTextResponse(body, HTTP_FORBIDDEN))
            return false;
        return true;
    }

    if (!cam_->getPhoto()) {
        cam_->close();
        body = "<html><body><h1><font color=\"red\">Fail to get photo</font></h1></body></html>";
        if (!client->sendTextResponse(body, HTTP_FORBIDDEN))
            return false;
        return true;
    }

    cam_->savePhoto("/tmp/photo" + to_string(cam) + ".jpg");
    cam_->close();

    if (!client->sendImageResponse("/tmp/photo" + to_string(cam) + ".jpg"))
        return false;

    return true;
}
