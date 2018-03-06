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

#include "syshandler.hpp"
#include "system.hpp"
#include "utils.hpp"

#include <vector>


SystemHandler::SystemHandler(const shared_ptr<ILog> &log,
                             const shared_ptr<ISystem> &sys):
                             log_(std::move(log)),
                             sys_(std::move(sys))
{
}

bool SystemHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    int temp;
    vector<string> parts;
    vector<string> ledParts;

    auto response = [&](const string &body) {
        if (!client->sendTextResponse(body, HTTP_OK))
            return false;
        else return true;
    };

    if (splitString(ledParts, request, "&")) {
        if (ledParts[0] == "cmd=power_led") {
            if (ledParts[1] == "state=1") {
                sys_->switchPowerLed(true);
                return response("{\"result\": true}");
            }
            if (ledParts[1] == "state=0") {
                sys_->switchPowerLed(false);
                return response("{\"result\": true}");
            }
            return false;
        }
        if (ledParts[0] == "cmd=status_led") {
            if (ledParts[1] == "state=1") {
                sys_->switchStatusLed(true);
                return response("{\"result\": true}");
            }
            if (ledParts[1] == "state=0") {
                sys_->switchStatusLed(false);
                return response("{\"result\": true}");
            }
            return false;
        }
        return false;
    }

    if (!splitString(parts, request, "="))
        return false;

    if (parts[1] == "cpu_temp") {
        if (!sys_->getCpuTemp(temp)) {
            return response("{\"result\": false}");
        } else {
            return response("{\"result\": true, \"temp\": " + to_string(temp) + "}");
        }
    }

    if (parts[1] == "reboot") {
        sys_->reboot();
        return response("{\"result\": true}");
    }

    if (parts[1] == "poweroff") {
        sys_->powerOff();
        return response("{\"result\": true}");
    }
    return false;
}
