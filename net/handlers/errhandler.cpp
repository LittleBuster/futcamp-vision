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

#include "errhandler.hpp"


bool ErrorHandler::process(const shared_ptr<IHttpClient> &client, const string &request)
{
    (void)request;
    string body = "<html><body><h1>403<br>Forbidden</h1></body></html>";

    if (!client->sendTextResponse(body, HTTP_FORBIDDEN))
        return false;

    return true;
}
