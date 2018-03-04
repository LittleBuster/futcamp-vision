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
#include "pageparser.hpp"
#include "path.hpp"


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
    auto parser = make_shared<PageParser>();
    string imgList = "";
    string outPage;

    if (!parser->loadFromFile(Path::getInstance().getPath("PhotoPage"))) {
        log_->error("Load 403.html failed: " + parser->getLastError(), "ERROR");
        return false;
    }

    auto pc = cfg_->getPhoto();

    for (unsigned i = 0; i < camCount; i++) {
        imgList += "<a><b>Camera " + to_string(i) + "</b></a><br><br>";
        imgList += "<img width=\"" + to_string(pc.width) + "\" height=\""
                + to_string(pc.height) + "\" src=\"/cam?dev=" + to_string(i) + "\" /><br>";
    }
    parser->setValue(0, imgList);
    parser->buildPage(outPage);

    if (!client->sendTextResponse(outPage, HTTP_OK))
        return false;

    return true;
}
