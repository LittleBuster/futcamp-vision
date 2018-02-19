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

#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <memory>

using namespace std;


class ITcpClient
{
public:
    virtual bool connect(std::string &ip, unsigned port) = 0;
    virtual bool send(const void *data, size_t len) const = 0;
    virtual bool recv(void *data, size_t len) const = 0;
    virtual void close() = 0;
    virtual int getSock() const = 0;
    virtual const string &getIp() const = 0;
};


class TcpClient: public ITcpClient
{
public:
    TcpClient();

    /**
     * @brief Create socket with old socket
     *
     * @param client Old client
     * @param ip Address of client
     */
    TcpClient(int client, const std::string &ip);

    /**
     * @brief Connecting to tcp server
     *
     * @param ip Server address
     * @param port Server port
     *
     * @return true If client connected
     * @return false If fail connected
     */
    bool connect(std::string &ip, unsigned port);

    /**
     * @brief Send data to server
     *
     * @param data Sending data
     * @param len Length of data
     *
     * @return true If send
     * @return false If fail sending
     */
    bool send(const void *data, size_t len) const;

    /**
     * @brief Receive data
     *
     * @param data Received data
     * @param len Length of data
     *
     * @return true If data received
     * @return false If fail receiving data
     */
    bool recv(void *data, size_t len) const;

    /**
     * @brief Close connection
     */
    void close();

    /**
     * @brief Get tcp socket
     *
     * @return sockfd Socket descriptor
     */
    inline int getSock() const { return sock_; }

    /**
     * @brief Get ip address
     *
     * @return ip Address of client
     */
    inline const string &getIp() const { return ip_; }

private:
    int sock_;
    string ip_;
};


#endif
