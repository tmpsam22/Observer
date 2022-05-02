#pragma once

#ifndef INCLUDE_FILE_OBSERVER_H
#define INCLUDE_FILE_OBSERVER_H

#include <observer_iface.h>
#include <string>
#include <chrono>
class FileObserver : public IObserver
{

public:

     FileObserver();

     void onNotify(const Subject& file) override;

private:

     std::time_t check_last_modified_time(const std::string& path);

     void set_modified_time(std::time_t modified_time);

     std::string serialize(std::time_t time);

private:

     std::time_t last_modified_time_;
};

#endif