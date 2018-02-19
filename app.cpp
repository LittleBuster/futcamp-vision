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

#include "app.hpp"
#include "path.hpp"


App::App(const shared_ptr<ILog> &log,
         const shared_ptr<IConfigs> &cfg,
         const shared_ptr<IHandlersMaker> &hmaker,
         const shared_ptr<IThreadManager> &tmanager,
         const shared_ptr<IDeviceServer> &server,
         const shared_ptr<ILocker> &locker):
         log_(std::move(log)),
         cfg_(std::move(cfg)),
         hmaker_(std::move(hmaker)),
         tmanager_(std::move(tmanager)),
         server_(std::move(server)),
         locker_(std::move(locker))
{
}

int App::start()
{
    log_->setLogFile(Path::getInstance().getPath("log"));

    locker_->addModule("LOG");

    server_->addHandler("/403", hmaker_->makeHandler("/403"));
    server_->addHandler("/404", hmaker_->makeHandler("/404"));
    server_->addHandler("/", hmaker_->makeHandler("/"));
    server_->addHandler("/sys", hmaker_->makeHandler("/sys"));
    server_->addHandler("/cam", hmaker_->makeHandler("/cam"));
    server_->addHandler("/photo", hmaker_->makeHandler("/photo"));

    if (!cfg_->loadFromFile(Path::getInstance().getPath("cfg"))) {
        log_->error("Configs error: " + cfg_->getLastError(), "HOUSEDEV");
        return -1;
    }
    log_->info("Configs loaded", "HOUSEDEV");

    auto sc = cfg_->getServer();
    server_->setParams(sc.port, sc.users, sc.threaded);

    tmanager_->addModule(server_);
    tmanager_->startAll();

    return 0;
}
