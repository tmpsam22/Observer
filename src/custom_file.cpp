#include <custom_file.h>
#include <filesystem>

customFile::customFile(const std::string& filename, std::ios_base::openmode openmode)
          : filename_(filename)
          , file_(filename, openmode)
{
     if (!file_)
     {
          std::runtime_error {"File:\t" + filename + " is invalid"};
     }
}

void customFile::writeToFile(const std::string& text, std::ios::openmode openmode)
{
     if (!file_.is_open())
     {
          file_.open(filename_, openmode);
     }
     file_ << text;
}

void customFile::closeFile()
{
     file_.close();
     update();
}

void customFile::openFile(const std::string& filename, std::ios::openmode openmode)
{
     if (filename != filename_)
     {
          file_.close();
          filename_ = filename;
     }

     file_.open(filename, openmode);
     update();
}

bool customFile::removeFile()
{
     bool is_removed = std::filesystem::remove(filename_);

     if (is_removed)
     {
          filename_ = "";
          update();
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
