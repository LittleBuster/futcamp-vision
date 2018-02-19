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

#include "cfgreader.hpp"


CfgReader::CfgReader(const string &filename): opened_(false)
{
    root_ = json_load_file(filename.c_str(), 0, nullptr);
    if(!root_)
        opened_ = false;
    else
        opened_ = true;
}

CfgReader::~CfgReader()
{
    json_decref(root_);
}

bool CfgReader::isOpen() const
{
    return opened_;
}

bool CfgReader::readString(const string &section, const string &name, string &value) const
{
    json_t *jobj, *jsobj;

    jobj = json_object_get(root_, section.c_str());
    if (jobj == nullptr)
        return false;

    jsobj = json_object_get(jobj, name.c_str());
    if (jsobj == nullptr)
        return false;

    value = string(json_string_value(jsobj));
    return true;
}

bool CfgReader::readInt(const string &section, const string &name, int &value) const
{
    json_t *jobj, *jsobj;

    jobj = json_object_get(root_, section.c_str());
    if (jobj == nullptr)
        return false;

    jsobj = json_object_get(jobj, name.c_str());
    if (jsobj == nullptr)
        return false;

    value = (int)json_integer_value(jsobj);
    return true;
}

bool CfgReader::readDouble(const string &section, const string &name, double &value) const
{
    json_t *jobj, *jsobj;

    jobj = json_object_get(root_, section.c_str());
    if (jobj == nullptr)
        return false;

    jsobj = json_object_get(jobj, name.c_str());
    if (jsobj == nullptr)
        return false;

    value = json_real_value(jsobj);
    return true;
}

bool CfgReader::readBool(const string &section, const string &name, bool &value) const
{
    json_t *jobj, *jsobj;

    jobj = json_object_get(root_, section.c_str());
    if (jobj == nullptr)
        return false;

    jsobj = json_object_get(jobj, name.c_str());
    if (jsobj == nullptr)
        return false;

    value = json_boolean_value(jsobj);
    return true;
}
