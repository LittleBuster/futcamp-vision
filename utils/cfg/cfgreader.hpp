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

#ifndef CFG_READER_HPP
#define CFG_READER_HPP

#include <memory>
#include <fstream>

#include <jansson.h>

using namespace std;


/**
 * @brief Reading json construction from file and gets params
 * RAII style for safe
 */
class CfgReader
{
public:
    /**
     * @brief Loading configs file in memory
     *
     * @param filename Name of configs file.
     */
    CfgReader(const string &filename);

    /**
     * @breif Unloading configs file from memory
     */
    ~CfgReader();

    /**
     * @brief Reading string param from json configs file
     *
     * @param[in] section Json section
     * @param[in] name Name of param in section
     * @param[out] value Readed string value of param
     *
     * @return true If reading param ok
     * @return false If fail reading param
     */
    bool readString(const string &section, const string &name, string &value) const;

    /**
     * @brief Reading integer param from json configs file
     *
     * @param[in] section Json section
     * @param[in] name Name of param in section
     * @param[out] value Readed integer value of param
     *
     * @return true If reading param ok
     * @return false If fail reading param
     */
    bool readInt(const string &section, const string &name, int &value) const;

    /**
     * @brief Reading double param from json configs file
     *
     * @param[in] section Json section
     * @param[in] name Name of param in section
     * @param[out] value Readed double value of param
     *
     * @return true If reading param ok
     * @return false If fail reading param
     */
    bool readDouble(const string &section, const string &name, double &value) const;

    /**
     * @brief Reading boolean param from json configs file
     *
     * @param[in] section Json section
     * @param[in] name Name of param in section
     * @param[out] value Readed bool value of param
     *
     * @return true If reading param ok
     * @return false If fail reading param
     */
    bool readBool(const string &section, const string &name, bool &value) const;

    /**
     * @brief Checking file state.
     *
     * @return true If file opened.
     * @return false If file not opened.
     */
    bool isOpen() const;

private:
    json_t *root_;
    bool opened_;
};


#endif
