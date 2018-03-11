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

#include "httpclient.hpp"

#include <fstream>

#include <unistd.h>


HttpClient::HttpClient()
{
}

HttpClient::HttpClient(int client, const string &ip): TcpClient::TcpClient(client, ip)
{
}

bool HttpClient::recvRequest(string &request)
{
    char sym;
    bool found = false;

    request = "";

    while (true) {
        if (!TcpClient::recv(&sym, 1))
            return false;

        if (sym == ' ' && !found) {
            found = true;
            continue;
        }

        if (sym == ' ' && found)
            break;

        if (found)
            request += sym;
    }
    return true;
}

bool HttpClient::sendTextResponse(const string &text, HttpCode code)
{
    string respCode;

    switch (code) {
        case HTTP_OK:
            respCode = "200 OK";
            break;
        case HTTP_NOT_FOUND:
            respCode = "404 Not Found";
            break;
        case HTTP_FORBIDDEN:
            respCode = "403 Forbidden";
            break;
    }

    string header = "HTTP/1.1 " + respCode + "\r\n" +
                    "Content-Type: text/html; charset=UTF-8\r\n\r\n";

    if (!TcpClient::send(header.c_str(), header.size()))
        return false;
    if (!TcpClient::send(text.c_str(), text.size()))
        return false;

    return true;
}

bool HttpClient::sendJsonResponse(const string &json)
{
    string header = "HTTP/1.1 200 OK\r\n"
                    "Content-Type: application/json; charset=UTF-8\r\n\r\n";

    if (!TcpClient::send(header.c_str(), header.size()))
        return false;
    if (!TcpClient::send(json.c_str(), json.size()))
        return false;

    return true;
}

bool HttpClient::sendFileResponse(const string &filename, HttpFileType type)
{
    string header;
    char buf[512];

    auto getFileType = [&](HttpFileType type) {
        switch (type) {
            case HTTP_CSS_FILE:
                return "text/css";
            case HTTP_JS_FILE:
                return "text/javascript";
            case HTTP_TXT_FILE:
                return "text/plain";
            case HTTP_GIF_FILE:
                return "image/gif";
            case HTTP_JPG_FILE:
                return "image/jpeg";
            case HTTP_PNG_FILE:
                return "image/png";
        }
        return "text/plain";
    };

    ifstream file(filename, ios::binary);
    if (!file.is_open())
        return false;

    file.seekg(0, ios_base::end);

    header = "HTTP/1.1 200 OK\r\n"
             "Connection: Keep-Alive\r\n"
             "Content-Type: " + string(getFileType(type)) + "; charset=UTF-8\r\n"
             "Content-Length: " + to_string(file.tellg()) + "\r\n\r\n";

    file.seekg(0, ios_base::beg);

    if (!TcpClient::send(header.c_str(), header.size())) {
        file.close();
        return false;
    }

    while (!file.eof()) {
        file.read(buf, 512);
        if (!TcpClient::send(buf, 512)) {
            file.close();
            return false;
        }
        usleep(100);
    }

    file.close();
    return true;
}

void HttpClient::close()
{
    TcpClient::close();
}
