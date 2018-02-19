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

#include "tcpserver.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <functional>

#include <thread>

using namespace std;


bool TcpServer::bindServer(unsigned port, unsigned clients, bool threaded)
{
    int ret;
    struct sockaddr_in sockAddr;

    auto ipInStr = [&](const struct sockaddr &addr) {
        string ip = "";

        for (unsigned i = 2; i < 6; i++) {
            ip += string(to_string((int)addr.sa_data[i]));
            if (i != 5)
                ip += ".";
        }
        return ip;
    };

    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0) {
        error_ = "Fail init socket.";
        return false;
    }

    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = INADDR_ANY;
    sockAddr.sin_port = htons(port);

    int enable = 1;
    if (setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        error_ = "Fail set sock option.";
        return false;
    }

    ret = bind(sock_, (struct sockaddr *)&sockAddr, sizeof(sockAddr));
    if (ret < 0) {
        error_ = "Fail binding server. Port already in use.";
        return false;
    }

    ret = listen(sock_, clients);
    if (ret < 0) {
        error_ = "Fail server listening.";
        return false;
    }

    serverStarted();

    while (true) {
        struct sockaddr addr;
        unsigned size = sizeof(addr);

        int sClient = accept(sock_, &addr, &size);
        if (sClient < 0) {
            acceptError();
            continue;
        }
        auto client = make_shared<TcpClient>(sClient, ipInStr(addr));
        if (threaded) {
            thread th(bind(&TcpServer::newSession, this, client));
            th.detach();
        } else {
            newSession(client);
        }
    }
    return true;
}
