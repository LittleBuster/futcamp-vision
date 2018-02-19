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

#include "indexhandler.hpp"


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
    int temp;
    unsigned camCount = cam_->getCamCount();

    string body = "<html><body><h1><center>Система<br></center>";

    if (!sys_->getCpuTemp(temp))
        body += "CPU temp: <font color=\"red\">fail</font><br>";
    else
        body += "CPU temp: " + to_string(temp) + "°<br>";
    body += "<a href=\"/sys?cmd=reboot\">Перезагрузка</a><br>";
    body += "<a href=\"/sys?cmd=poweroff\">Выключение</a><br>";

    body += "<center>Камеры</center><br>";
    body += "Количество: " + to_string(camCount) + "<br>";
    body += "<a href=\"/photo\">Смотреть фото</a><br>";
    body += "</h1></body></html>";

    if (!client->sendTextResponse(body, HTTP_OK))
        return false;

    return true;
}
