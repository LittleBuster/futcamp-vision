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

#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;


class ICamera
{
public:
    virtual bool open(unsigned number) = 0;
    virtual bool getPhoto() = 0;
    virtual unsigned getCamCount() = 0;
    virtual void savePhoto(const string &filename) = 0;
    virtual void close() = 0;
};


class Camera: public ICamera
{
public:
    /**
     * @brief Open camera device
     *
     * @param number Number of camera
     *
     * @return true If camera openned
     * @return false If fail to open cam device
     */
    bool open(unsigned number);

    /**
     * @brief Get count of cam on device
     */
    unsigned getCamCount();

    /**
     * @brief Get photo from device
     *
     * @return true If photo got
     * @return false If fail to get photo
     */
    bool getPhoto();

    /**
     * @brief Save photo to local storage
     *
     * @param filename Path to file
     */
    void savePhoto(const string &filename);

    /**
     * @brief Close camera device
     */
    void close();

private:
    CvCapture* capture_;
    IplImage* frame_;
};


#endif
