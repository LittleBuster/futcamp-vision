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

#include "httpserver.hpp"


bool HttpServer::bindServer(unsigned port, unsigned clients, bool threaded)
{
    return TcpServer::bindServer(port, clients, threaded);
}

void HttpServer::serverStarted() const
{
    serverHttpStarted();
}

void HttpServer::acceptError() const
{
    acceptHttpError();
}

void HttpServer::newSession(const shared_ptr<ITcpClient> &client)
{
    auto httpClient = make_shared<HttpClient>(client->getSock(), client->getIp());
    newHttpSession(httpClient);
    httpClient->close();
}
