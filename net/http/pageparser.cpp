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


PageLoader::PageLoader(const string &filename, string &buf)
{
    string line;
    buf = "";

    file_.open(filename, ios::in);
    if (!file_.is_open()) {
        setLoadStatus(false);
        return;
    }

    while (!file_.eof()) {
        file_ >> line;
        buf = buf + line;
    }
}

PageLoader::~PageLoader()
{
    if (file_.is_open())
        file_.close();
}


bool PageParser::loadFromFile(const string &filename)
{
    unsigned paramsCount;
    string pageContent;
    PageLoader loader(filename, pageContent);

    if (!loader.getLoadStatus()) {
        error_ = "Fail to load page content";
        return false;
    }

    if (!splitString(parts_, pageContent, "<%PARAM%>")) {
        error_ = "Fail to split page content by params";
        return false;
    }

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
