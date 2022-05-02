#pragma once

#ifndef INCLUDE_CUSTOM_FILE_H
#define INCLUDE_CUSTOM_FILE_H

#include <string>
#include <fstream>
#include <subject.h>
#include <functional>

class customFile final : public Subject
{

public:

     enum class responseToObservers : int
     {
          notification_on,
          notification_off
     };

public:

     customFile();

     customFile(const std::string& filename, std::ios::openmode openmode);

     void writeToFile(const std::string& text, responseToObservers response = responseToObservers::notification_off,
          std::ios::openmode openmode = std::ios::out);

     void closeFile(responseToObservers response = responseToObservers::notification_off);

     void openFile(const std::string& filename, responseToObservers response = responseToObservers::notification_off,
          std::ios::openmode openmode = std::ios::out);

     bool removeFile(responseToObservers response = responseToObservers::notification_off);

     std::string getFilename() const;

     ~customFile() override;

     void update();

private:

     std::string filename_;

     std::fstream file_;
};


#endif