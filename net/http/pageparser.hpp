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

#ifndef PAGE_PARSER
#define PAGE_PARSER

#include <string>
#include <vector>
#include <fstream>


using namespace std;


#define HTML_STRING_LEN 4096


class PageLoader
{
public:
    /**
     * @brief Loading page from file
     *
     * @param filename Path to page .html file
     *
     * @param[out] buf Page content
     */
    PageLoader(const string &filename, string &buf);

    /**
     * @brief Page content load status
     *
     * @return true If page loaded
     * @return false If fail to load page
     */
    inline bool getLoadStatus() { return loadStatus_; }

    /**
     * @brief Set page load status
     *
     * @param status Loaded status
     */
    inline void setLoadStatus(bool status) { loadStatus_ = status; }

    /**
     * Unloading page file
     */
    ~PageLoader();

private:
    ifstream file_;
    bool loadStatus_;
};


class PageParser
{
public:
    /**
     * @brief Loading page from .html file
     *
     * @param filename Path to .html file
     *
     * @return true If page loaded
     * @return false If fail to load page from file
     */
    bool loadFromFile(const string &filename);

    /**
     * @brief Building output page
     *
     * @param outPage Output page content with all params
     */
    void buildPage(string &outPage);

    /**
     * @brief Set value for param
     *
     * @param paramIndex Param number
     * @param value Param new value
     */
    inline void setValue(unsigned paramIndex, const string &value) { params_[paramIndex] = value; }

    /**
     * @brief Get last error
     *
     * @return Error string
     */
    inline const string& getLastError() { return error_; }

private:
    vector<string> parts_;
    vector<string> params_;
    string error_;
};


#endif
