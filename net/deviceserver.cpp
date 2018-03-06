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

#include "deviceserver.hpp"
#include "utils.hpp"

#include <vector>


DeviceServer::DeviceServer(const shared_ptr<ILog> &log):
                           log_(std::move(log))
{
}

void DeviceServer::addHandler(const string &name, const shared_ptr<IHandler> &handler)
{
    handlers_.insert(make_pair(name, handler));
}

void DeviceServer::setParams(unsigned port, unsigned users, bool threaded)
{
    port_ = port;
    users_ = users;
    threaded_ = threaded;
}

void DeviceServer::start()
{
    if (!bindServer(port_, users_, threaded_)) {
        log_->error("Fail to start server: " + getLastError(), "SERVER");
        exit(1);
    }
}

bool DeviceServer::bindServer(unsigned port, unsigned clients, bool threaded)
{
    return HttpServer::bindServer(port, clients, threaded);
}

void DeviceServer::serverHttpStarted() const
{
    log_->info("Server started", "SERVER");
}

void DeviceServer::acceptHttpError() const
{
    log_->info("Accept error", "SERVER");
}

void DeviceServer::newHttpSession(const shared_ptr<IHttpClient> &client)
{
    string request;
    vector<string> parts;

    client->recvRequest(request);

    if (request == "/") {
        if (!handlers_[request]->process(client, request))
            handlers_["/403"]->process(client, request);
        return;
    }

    if (request == "/photo") {
        if (!handlers_[request]->process(client, request))
            handlers_["/403"]->process(client, request);
        return;
    }

    if (request.find("/files") == 0) {
        if (!handlers_["/files"]->process(client, request))
            handlers_["/403"]->process(client, request);
        return;
    }

    if (!splitString(parts, request, "?")) {
        handlers_["/403"]->process(client, request);
        return;
    }

    auto handler = handlers_[parts[0]];
    if (handler != nullptr) {
        if (!handler->process(client, parts[1]))
            handlers_["/403"]->process(client, parts[1]);
    } else {
        if (!handlers_["/404"]->process(client, request))
            handlers_["/403"]->process(client, request);
    }
}
