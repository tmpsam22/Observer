#include <iostream>
#include <list>
#include <fstream>
#include <vector>
#include <filesystem>
#include <memory>

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
     void notify(const Subject& subject, filechanges price)
     {
          for(auto& val : observers_) { val->onNotify(subject); }
     }


private:
     std::list<IObserver *> observers_;
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
          notify(*this, filechanges::exist);
     }
     void writeToFile(const std::string& text)
     {
          if (file_.is_open())
          {
               file_ << text;
          }
          notify(*this, filechanges::changed);
     }
     bool removeFile(const std::string& filename)
     {
          bool is_removed = std::filesystem::remove(filename);
          if (is_removed)
          {
               notify(*this, filechanges::removed);
          }
          return is_removed;
     }
     std::string getFilename() const { return filename_; }
     ~customFile() { file_.close(); }
private:
     std::string filename_;
     std::fstream file_;
};

struct FileObserver : IObserver
{
     void onNotify(const customFile& file, filechanges changes) override // draft
     {
          namespace fs = std::filesystem;
          switch(changes)
          {
               case filechanges::changed :
                    std::cout << "File was changed" << std::endl;
               case filechanges::exist  :
                    std::cout << "filename:\t" << file.getFilename() << std::endl;
                    std::cout << "is exits" << fs::exists(file.getFilename()) <<  std::endl;
                    std::cout << "is empty:\t" << fs::is_empty(file.getFilename()) << std::endl;
                    if (fs::exists(file.getFilename()) && !fs::is_empty(file.getFilename()) )
                    {
                         std::cout << fs::file_size(file.getFilename()) << std::endl;
                    }
               case filechanges::removed :
                    if (!fs::exists(file.getFilename())) {
                         std::cout << "file is removed" << std::endl;
                    }
                    break;
               default :
                    throw std::runtime_error{"Hello world"};
          }
     }
};


int main(int argc, char** argv) try
{
     const std::string filepath = argc == 2 ? argv[1] : "default.txt";
     std::cout << filepath << std::endl;
     customFile file(filepath, std::ios_base::out);
     auto pObserver = std::make_unique<FileObserver>();
     file.addObserver(pObserver.get());
     file.writeToFile("hihfdsafdasfdsafdsafadsfadsfdsafdsihih");
     //file.removeFile(filepath);
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