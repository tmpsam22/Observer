#include <file_observer.h>
#include <custom_file.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <filesystem>

void FileObserver::onNotify(const Subject& file)
{
     namespace fs = std::filesystem;
     auto&& file_ =  static_cast<const customFile&> (file);
     const std::string filename = file_.getFilename();
     if (fs::exists(filename))
     {
          const std::time_t current_modified_time = check_last_modified_time(filename);
          if (fs::is_empty(filename))
          {
               std::cout << "[OBSERVER] : " << "The file is empty but" << std::endl;
               std::cout << "\twas created in:\t" << serialize(current_modified_time) << std::endl;
               return;
          }

          if (!last_modified_time_)
          {
               set_modified_time(current_modified_time);
          }

          std::string to_out_ {"[OBSERVER] : The file exists.\nLast modified time:\t" + serialize(last_modified_time_)};
          if (last_modified_time_ && (current_modified_time != last_modified_time_))
          {
               to_out_ = "[OBSERVER] : The file has been changed.\nCurrent modified time:\t" + serialize(current_modified_time)
                         + "Last modified time:\t" + serialize(last_modified_time_);
               set_modified_time(current_modified_time);
          }
          std::cout << to_out_ << "Size:\t" << fs::file_size(filename) << std::endl;
          return;
     }

     std::cout << "[OBSERVER] : " << "The file was removed!" << std::endl;
}

std::time_t FileObserver::check_last_modified_time(const std::string& path)
{
     auto ftime = std::filesystem::last_write_time(path);
     return std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
}

void FileObserver::set_modified_time(std::time_t modified_time)
{
     last_modified_time_ = modified_time;
}

std::string FileObserver::serialize(std::time_t time)
{
     return std::asctime(std::localtime(&time));
}

FileObserver::FileObserver()
     : last_modified_time_ { 0 }
{

}