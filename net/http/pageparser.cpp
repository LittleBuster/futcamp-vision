/*****************************************************************************
 *
 * Future Camp Project
 *
 * Copyright (C) 2018 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 *****************************************************************************/

#include "pageparser.hpp"
#include "utils.hpp"

#include <string.h>


PageLoader::PageLoader(const string &filename, string &buf)
{
    char line[HTML_STRING_LEN];
    buf = "";

    file_.open(filename, ios::in);
    if (!file_.is_open()) {
        setLoadStatus(false);
        return;
    }

    while (!file_.eof()) {
        memset(line, 0x0, HTML_STRING_LEN);
        file_.read(line, HTML_STRING_LEN);
        buf += string(line);
    }
    setLoadStatus(true);
}

PageLoader::~PageLoader()
{
    if (file_.is_open())
        file_.close();
}


bool PageParser::loadFromFile(const string &filename)
{
    unsigned paramsCount;
    PageLoader loader(filename, pageContent_);

    if (!loader.getLoadStatus()) {
        error_ = "Page have not params";
        return false;
    }

    if (!splitString(parts_, pageContent_, "<%PARAM%>"))
        return true;

    paramsCount = parts_.size() - 1;
    for (unsigned i = 0; i < paramsCount; i++)
        params_.push_back("");

    return true;
}

void PageParser::buildPage(string &outPage)
{
    outPage = "";

    for (unsigned i = 0; i < params_.size(); i++)
        outPage += parts_[i] + params_[i];

    outPage += parts_[params_.size()];
}
