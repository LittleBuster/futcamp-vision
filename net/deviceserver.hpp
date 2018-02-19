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

#ifndef DEVICE_SERVER_HPP
#define DEVICE_SERVER_HPP

#include "httpclient.hpp"
#include "httpserver.hpp"
#include "log.hpp"
#include "imodule.hpp"
#include "ihandler.hpp"
#include "configs.hpp"

#include <map>


class IDeviceServer: public IHttpServer, public IModule
{
public:
    virtual void addHandler(const string &name, const shared_ptr<IHandler> &handler) = 0;
    virtual void setParams(unsigned port, unsigned users, bool threaded) = 0;
    virtual void start() = 0;
};


class DeviceServer: public IDeviceServer, public HttpServer
{
public:
    DeviceServer(const shared_ptr<ILog> &log);

    /**
     * @brief Add new handler to server
     *
     * @param name Name of handler
     * @param handler New handler
     */
    void addHandler(const string &name, const shared_ptr<IHandler> &handler);

    /**
     * @brief setParams
     *
     * @param port Web server port
     * @param users Maximum users in queue
     * @param threaded Multi-threaded server
     *
     */
    void setParams(unsigned port, unsigned users, bool threaded);

    /**
     * @brief Starting server
     */
    void start();

    /**
     * @brief Start http server
     *
     * @param port Tcp binding port
     * @param clients Maximum clients
     * @param threaded Is multi-threaded server
     *
     * @return true If server started and cancelled
     * @return false If fail binding tcp server
     */
    bool bindServer(unsigned port, unsigned clients, bool threaded) override final;

    /**
     * @brief Start http server callback
     */
    virtual void serverHttpStarted() const override final;

    /**
     * @brief Accept new http client error
     */
    virtual void acceptHttpError() const override final;

    /**
     * @brief New http client connection
     *
     * @param client New http client
     */
    virtual void newHttpSession(const shared_ptr<IHttpClient> &client) override final;

    /**
     * @brief Get last error
     *
     * @return Last error string
     */
    inline const string &getLastError() const { return HttpServer::getLastError(); }

private:
    const shared_ptr<ILog> log_;

    unsigned port_;
    unsigned users_;
    bool threaded_;
    map<string, shared_ptr<IHandler>> handlers_;
};


#endif
