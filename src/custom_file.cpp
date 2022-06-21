#include <custom_file.h>
#include <filesystem>

customFile::customFile(
          const std::string& filename,
          std::ios_base::openmode openmode
)
          : filename_(filename)
          , file_(filename, openmode)
{
     if (!file_)
     {
          std::runtime_error {"File:\t" + filename + " is invalid"};
     }
}

void customFile::writeToFile(
     const std::string& text,
     std::ios::openmode openmode,
     responseToObservers response
)
{
     file_.clear();

     if (!file_.is_open())
     {
          file_.open(filename_, openmode);
     }

     file_ << text;

     if (response == responseToObservers::notification_on)
     {
          update();
     }
}

void customFile::closeFile(responseToObservers response)
{
     file_.close();
     if (response == responseToObservers::notification_on)
     {
          update();
     }
}

void customFile::openFile(
     const std::string& filename,
     std::ios::openmode openmode,
     responseToObservers response
)
{
     if (filename != filename_)
     {
          file_.close();
          filename_ = filename;
     }

     file_.open(filename, openmode);
     if (response == responseToObservers::notification_on)
     {
          update();
     }
}

bool customFile::removeFile(responseToObservers response)
{
     bool is_removed = std::filesystem::remove(filename_);

     if (is_removed)
     {
          filename_ = "";
          if (response == responseToObservers::notification_on)
          {
               update();
          }
     }
     return is_removed;
}

std::string customFile::getFilename() const
{
     return filename_;
}

customFile::~customFile()
{
     file_.close();
}

void customFile::update()
{
     notify(*this);
}

customFile::customFile()
     : filename_ { }
     , file_  { }
{
}