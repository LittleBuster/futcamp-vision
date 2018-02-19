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

#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include "tcpclient.hpp"
#include "tcpserver.hpp"
#include "httpclient.hpp"


class IHttpServer
{
public:
    virtual bool bindServer(unsigned port, unsigned clients, bool threaded) = 0;
    virtual void serverHttpStarted() const = 0;
    virtual void acceptHttpError() const = 0;
    virtual void newHttpSession(const shared_ptr<IHttpClient> &client) = 0;
};


class HttpServer: public IHttpServer, public ITcpServer, public TcpServer
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
     * @brief Start http server callback
     */
    void serverHttpStarted() const { }

    /**
     * @brief Accept new http client error
     */
    void acceptHttpError() const { }

    /**
     * @brief New http client connection
     *
     * @param client New http client
     */
    virtual void newHttpSession(const shared_ptr<IHttpClient> &client) { (void)client; }

    /**
     * @brief Get last error
     *
     * @return Last error string
     */
    inline const string &getLastError() const { return TcpServer::getLastError(); }

private:

    /**
     * @brief Start server signal
     */
    void serverStarted() const override final;

    /**
     * @brief Accept new client error
     */
    void acceptError() const override final;

    /**
     * @brief New client connected callback
     *
     * @param client New client
     * @param addr Ip address of new client
     */
    void newSession(const shared_ptr<ITcpClient> &client) override final;
};


#endif
