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

#include "camera.hpp"


bool Camera::open(unsigned number)
{
    capture_ = cvCreateCameraCapture(number);

    if (capture_ == nullptr)
        return false;
    return true;
}

unsigned Camera::getCamCount()
{
    unsigned count = 0;

    while (true) {
        CvCapture *cam = cvCreateCameraCapture(count);
        if (cam == nullptr)
            break;
        cvReleaseCapture(&cam);
        count++;
    }
    return count;
}

bool Camera::getPhoto()
{
    frame_ = cvQueryFrame(capture_);

    if (frame_ == nullptr)
        return false;
    return true;
}

void Camera::savePhoto(const string &filename)
{
    cvSaveImage(filename.c_str(), frame_, 0);
}

void Camera::close()
{
    if (frame_ != nullptr)
        cvReleaseImage(&frame_);
    if (capture_ != nullptr)
        cvReleaseCapture(&capture_);
}
