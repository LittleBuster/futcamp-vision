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

#include "tcpclient.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


TcpClient::TcpClient()
{
    sock_ = -1;
}

TcpClient::TcpClient(int client, const string &ip)
{
    sock_ = client;
    ip_ = ip;
}

bool TcpClient::connect(string &ip, unsigned port)
{
    int retVal;
    struct sockaddr_in addr;

    memset(&addr, 0x0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);

    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ < 0)
        return false;

    retVal = ::connect(sock_, (struct sockaddr *)&addr, sizeof(addr));
    if (retVal < 0)
        return false;

    return true;
}

bool TcpClient::send(const void *data, size_t len) const
{
    int retVal = 0;

    for (;;) {
        retVal = ::send(sock_, data, len, MSG_NOSIGNAL);
        if (retVal < 0)
            return false;

        if (retVal == (int)len)
            break;
    }
    return true;
}

bool TcpClient::recv(void *data, size_t len) const
{
    int retVal;
    int total;
    unsigned char *cdata = (unsigned char *)data;

    retVal = ::recv(sock_, cdata, len, MSG_NOSIGNAL);
    total = len - retVal;
    if (total == 0)
        return true;

    while (total != 0) {
        retVal = ::recv(sock_, cdata + retVal, total, MSG_NOSIGNAL);
        total = total - retVal;
    }
    return false;
}

void TcpClient::close()
{
    if (sock_ > 0) {
        ::shutdown(sock_, 1);
        ::close(sock_);
    }
}
