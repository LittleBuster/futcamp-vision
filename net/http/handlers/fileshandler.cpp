/*****************************************************************************
 *
 * Future Camp Project
 *
 * Copyright (C) 2018 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 *****************************************************************************/

#include "fileshandler.hpp"
#include "pageparser.hpp"
#include "path.hpp"
#include "utils.hpp"
#include "httpclient.hpp"


FilesHandler::FilesHandler(const shared_ptr<ILog> &log,
                           const shared_ptr<IConfigs> &cfg):
                           log_(std::move(log)),
                           cfg_(std::move(cfg))
{
}

bool FilesHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    vector<string> parts, ext;
    auto parser = make_shared<PageParser>();
    auto ptc = cfg_->getPath();

    auto getFileType = [&](const string &extension) {
        if (extension == "jpg" || extension == "jpeg")
            return HTTP_JPG_FILE;
        if (extension == "gif")
            return HTTP_GIF_FILE;
        if (extension == "css")
            return HTTP_CSS_FILE;
        if (extension == "png")
            return HTTP_PNG_FILE;
        if (extension == "gif")
            return HTTP_GIF_FILE;
        if (extension == "txt" || extension == "conf" || extension == "cfg"
                               || extension == "html" || extension == "htm")
            return HTTP_TXT_FILE;
        if (extension == "js")
            return HTTP_JS_FILE;
        return HTTP_TXT_FILE;
    };

    splitString(parts, request, "/");
    if (parts.size() != 4)
        return false;

    if (!splitString(ext, parts[3], "."))
        return false;

    if (!client->sendFileResponse(ptc.files + parts[2] + "/" + parts[3], getFileType(ext[1])))
        return false;

    return true;
}
