#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <filesystem>
#include <memory>
#include <chrono>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <random>

enum class filechanges: int
{
     undefined,
     exist,
     removed,
     changed
};

struct customFile;
struct Subject;

struct IObserver
{
     virtual void onNotify(const Subject&) = 0;
     virtual ~IObserver() { }
};

struct Subject
{

     void addObserver(IObserver* observer)
     { observers_.push_back ( observer ); }

     void removeObserver(IObserver* observer) { /*std::remove(std::begin(observers_), std::end(observers_), observer);*/ }
     // { }/observers_.erase( std::remove(observers_.begin(), observers_.end(), observer) , observers_.end() ); };
protected:
     void notify(const Subject& subject)
     {
          for(auto& val : observers_) { val->onNotify(subject); }
     }


private:
     std::list<IObserver*  > observers_;
};

struct customFile : Subject
{
     customFile(const std::string& filename, std::ios_base::openmode openmode)
          : filename_(filename)
          , file_(filename, openmode)
     {
          if (!file_)
          {
               std::runtime_error {"File:\t" + filename + " is invalid"};
          }
     }

     void writeToFile(const std::string& text, std::ios::openmode openmode = std::ios::out)
     {
          if (!file_.is_open())
          {
               file_.open(filename_, openmode);
          }
          file_ << text;
     }

     void closeFile() { file_.close(); update(); }
     void openFile(const std::string& filename, std::ios::openmode openmode = std::ios::out)
     {
          if (filename != filename_)
          {
               file_.close();
               filename_ = filename;
          }

          file_.open(filename, openmode);
          update();
     }

     bool removeFile()
     {
          bool is_removed = std::filesystem::remove(filename_);

          if (is_removed)
          {
               filename_ = "";
               update();
          }
          return is_removed;
     }

     std::string getFilename() const { return filename_; }
     ~customFile() { file_.close();}
     void update()  { notify(*this);  }
private:
     std::string filename_;
     std::fstream file_;
};

struct FileObserver : IObserver
{
     void onNotify(const Subject& file) override // draft
     {
          namespace fs = std::filesystem;
          auto&& file_ =  static_cast<const customFile&> (file);
          const std::string filename = file_.getFilename();
          if (fs::exists(filename)) // check to empty
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
private:

     std::string check_last_modified_time(const std::string& path)
     {
          auto ftime = std::filesystem::last_write_time(path);
          std::time_t cftime = std::chrono::system_clock::to_time_t(std::chrono::file_clock::to_sys(ftime));
          return std::asctime(std::localtime(&cftime));
     }

     void set_modified_time(const std::string& modified_time)
     {
          last_modified_time_ = modified_time;
     }

private:
     std::string last_modified_time_;
};

int main(int argc, char** argv) try
{
     namespace fs =  std::filesystem;
     const std::string filepath = argc == 2 ? argv[1] : "../default.txt";
     std::cout << filepath << std::endl;
     customFile file(filepath, std::ios_base::out);
     auto observer = std::make_unique<FileObserver>();
     file.addObserver(observer.get());
     #ifdef TEST
          auto shuffle_string = [](std::size_t lenght)
          {
               std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
               std::random_device rd;
               std::mt19937 generator(rd());
               std::shuffle(str.begin(), str.end(), generator);
               return str.substr(0, lenght);
          };
          while (true)
          {
               std::this_thread::sleep_for(std::chrono::seconds(3));
               std::srand(std::time(nullptr));
               int rand_value = std::rand() % 3 + 1;
               switch (rand_value)
               {
                    case 1 :
                         std::cout << "**\nRewrite a file" << std::endl;
                         file.openFile(filepath);
                         std::cout << "**\n";
                         break;
                    case 2:
                    {
                         std::string to_write_ = shuffle_string(std::rand() % 50 + 1);
                         std::cout << "**\nWriting to file:" << to_write_ << std::endl;
                         file.writeToFile(to_write_);
                         std::this_thread::sleep_for(std::chrono::seconds(1));
                         file.closeFile();
                         std::cout << "**\n";
                         break;
                    }
                    case 3:
                         std::cout << "Removing a file" << std::endl;
                         file.removeFile();
                         file.openFile(filepath);
               }
          }
     #endif
     return EXIT_SUCCESS;
}
catch(std::exception& e)
{
     std::cerr << e.what() << std::endl;
     return EXIT_FAILURE;
}
catch(...)
{
     return EXIT_FAILURE;
}