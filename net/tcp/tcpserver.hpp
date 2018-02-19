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

#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

#include <tuple>
#include <string>

#include "tcpclient.hpp"

using namespace std;


class ITcpServer
{
public:
    virtual bool bindServer(unsigned port, unsigned clients, bool threaded) = 0;
    virtual void newSession(const shared_ptr<ITcpClient> &client) = 0;
    virtual void serverStarted() const = 0;
    virtual void acceptError() const = 0;
    virtual const string &getLastError() const = 0;
};


class TcpServer: public ITcpServer
{
public:
    /**
     * @brief Start tcp server
     *
     * @param port Tcp binding port
     * @param clients Maximum clients
     *
     * @return true If server started and cancelled
     * @return false If fail binding tcp server
     */
    bool bindServer(unsigned port, unsigned clients, bool threaded);

    /**
     * @brief New client connected callback
     *
     * @param client New client
     * @param addr Ip address of new client
     */
    void newSession(const shared_ptr<ITcpClient> &client) { (void)client; }

    /**
     * @brief Start server callback
     */
    void serverStarted() const { }

    /**
     * @brief Accept new client error
     */
    void acceptError() const { }

    /**
     * @brief Get last error
     *
     * @return Last error string
     */
    inline const string &getLastError() const { return error_; }

private:
    int sock_;
    string error_;
};


#endif
