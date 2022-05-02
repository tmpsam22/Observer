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
          const std::string current_modified_time = check_last_modified_time(filename);
          if (fs::is_empty(filename))
          {
               std::cout << "File is empty" << std::endl;
               std::cout << "Created time:\t" << current_modified_time << std::endl;
               return;
          }
          if (last_modified_time_.empty())
          {
               set_modified_time(current_modified_time);
          }
          std::string to_out_ {"File exists.\nLast modifed time:\t" + last_modified_time_};
          if (!last_modified_time_.empty() && current_modified_time != last_modified_time_)
          {
               to_out_ = "File changed. \nCurrent modified time\t:" + current_modified_time +
                    +"Last modified time\t:" + last_modified_time_;
               set_modified_time(current_modified_time);
          }
          std::cout << to_out_ << "Size:\t" << fs::file_size(filename) << std::endl;
          return;
     }
     std::cout << "File was removed" << std::endl;
}

std::string FileObserver::check_last_modified_time(const std::string& path)
{
     auto ftime = std::filesystem::last_write_time(path);
     std::time_t cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
     return std::asctime(std::localtime(&cftime));
}

void FileObserver::set_modified_time(const std::string& modified_time)
{
     last_modified_time_ = modified_time;
}