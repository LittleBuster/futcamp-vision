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

#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <memory>

#include "tcpclient.hpp"

using namespace std;


typedef enum {
    HTTP_OK,
    HTTP_FORBIDDEN,
    HTTP_NOT_FOUND
} HttpCode;


class IHttpClient
{
public:
    virtual bool recvRequest(string &request) = 0;
    virtual bool sendTextResponse(const string &text, HttpCode code) = 0;
    virtual bool sendJsonResponse(const string &json) = 0;
    virtual bool sendImageResponse(const string &filename) = 0;
    virtual void close() = 0;
};


class HttpClient: public IHttpClient, private TcpClient
{
public:
    HttpClient();

    /**
     * @brief Create socket with old socket
     *
     * @param client Old client
     * @param ip Address of client
     */
    HttpClient(int client, const std::string &ip);

    /**
     * @brief Receiving request from http client
     *
     * @param request Request string
     *
     * @return true If request received
     * @return false If fail to receive request
     */
    bool recvRequest(string &request);

    /**
     * @brief Sending text response
     *
     * @param text Response body
     * @param code Http response code
     *
     * @return true If response sended
     * @return true If fail to send response
     */
    bool sendTextResponse(const string &text, HttpCode code);

    /**
     * @brief Sending json response
     *
     * @param json Response body
     *
     * @return true If response sended
     * @return true If fail to send response
     */
    bool sendJsonResponse(const string &json);

    /**
     * @brief Sending image response
     *
     * @param filename Path to image file
     *
     * @return true If response sended
     * @return true If fail to send response
     */
    bool sendImageResponse(const string &filename);

    /**
     * @brief Close connection
     */
    void close();
};


#endif
