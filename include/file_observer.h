#pragma once

#ifndef INCLUDE_FILE_OBSERVER_H
#define INCLUDE_FILE_OBSERVER_H

#include <observer_iface.h>
#include <string>

class FileObserver : public IObserver
{

public:

     void onNotify(const Subject& file) override;

private:

     std::string check_last_modified_time(const std::string& path);

     void set_modified_time(const std::string& modified_time);

private:

     std::string last_modified_time_;
};

#endif