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

#include "photohandler.hpp"


PhotoHandler::PhotoHandler(const shared_ptr<ILog> &log,
                           const shared_ptr<IConfigs> &cfg,
                           const shared_ptr<ICamera> &cam):
                           log_(std::move(log)),
                           cfg_(std::move(cfg)),
                           cam_(std::move(cam))
{

}

bool PhotoHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    (void)request;
    unsigned camCount = cam_->getCamCount();

    string body = "<html><body><center><h1>Фото с камер<br>";
    body += "<a href=\"/\">Назад</a><br>";

    auto pc = cfg_->getPhoto();

    for (unsigned i = 0; i < camCount; i++) {
        body += "Cam " + to_string(i) + "<br>";
        body += "<img width=\"" + to_string(pc.width) + "\" height=\""
             + to_string(pc.height) + "\" src=\"/cam?dev=" + to_string(i) + "\" /><br>";
    }
    body += "<a href=\"/\">Назад</a><br>";
    body += "</h1></center></body></html>";

    if (!client->sendTextResponse(body, HTTP_OK))
        return false;

    return true;
}
