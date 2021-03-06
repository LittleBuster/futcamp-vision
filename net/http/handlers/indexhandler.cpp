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

#include "indexhandler.hpp"
#include "path.hpp"
#include "pageparser.hpp"


IndexHandler::IndexHandler(const shared_ptr<ILog> &log,
                           const shared_ptr<ICamera> &cam,
                           const shared_ptr<ISystem> &sys):
                           log_(std::move(log)),
                           cam_(std::move(cam)),
                           sys_(std::move(sys))
{
}

bool IndexHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    (void)request;
    int temp, totalMem, usedMem;
    string totalDisk, usedDisk, uptime;
    string outPage;
    unsigned camCount = cam_->getCamCount();
    auto parser = make_shared<PageParser>();

    if (!parser->loadFromFile(Path::getInstance().getPath("IndexPage"))) {
        log_->error("Load index.html failed: " + parser->getLastError(), "INDEX");
        return false;
    }

    if (!sys_->getCpuTemp(temp))
        parser->setValue(0, "<font color=\"red\">Error</font>");
    else
        parser->setValue(0, to_string(temp));

    if (!sys_->getRamSize(totalMem, usedMem))
        parser->setValue(1, "<font color=\"red\">Error</font>");
    else
        parser->setValue(1, to_string(usedMem) + "/" + to_string(totalMem));

    if (!sys_->getDiskSpace(totalDisk, usedDisk))
        parser->setValue(2, "<font color=\"red\">Error</font>");
    else
        parser->setValue(2, usedDisk + "/" + totalDisk);

    if (!sys_->getUptime(uptime))
        parser->setValue(3, "<font color=\"red\">Error</font>");
    else
        parser->setValue(3, uptime);

    parser->setValue(4, to_string(camCount));
    parser->buildPage(outPage);

    if (!client->sendTextResponse(outPage, HTTP_OK))
        return false;
    return true;
}
