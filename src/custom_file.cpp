#include <custom_file.h>
#include <filesystem>
#include <iostream>

customFile::customFile(
          const std::string& filename,
          std::ios_base::openmode openmode
)
          : filename_{ filename }
          , file_{ filename, openmode }
{
     if (!file_) // если файл не открылся - выбрасываем исключение:
     {
          throw std::runtime_error {"File:\t" + filename + " is invalid"};
     }
}

void customFile::writeToFile(
     const std::string& text,
     std::ios::openmode openmode,
     responseToObservers response
)
{
     file_.clear(); // очищаем флаги

     if (!file_.is_open()) // если файл не открыт, то
     {
          file_.open(filename_, openmode); // открываем файл для записи с соответсвующим флагом
     }

     file_ << text; // записываем данные в файл

     if (response == responseToObservers::notification_on)
     {
          update(); // оповещаем наблюдателей
     }
}

void customFile::closeFile(responseToObservers response)
{
     file_.close(); // закрываем файл
     if (response == responseToObservers::notification_on)
     {
          update(); // оповещаем наблюдателей
     }
}

void customFile::openFile(
     const std::string& filename,
     std::ios::openmode openmode,
     responseToObservers response
)
{
     if (filename != filename_) // если имя текущего файла != имени,
                              // указанного в аргументе, то
     {
          file_.close(); // закрываем текущий файл
          filename_ = filename; // обновляем имя текущего файла
     }

     file_.open(filename, openmode); // открываем файл с нужным флагом открытия
     if (response == responseToObservers::notification_on)
     {
          update(); // оповещаем наблюдателей
     }
}

bool customFile::removeFile(responseToObservers response)
{
     if (!std::filesystem::exists(filename_)) // если не существует
     {
          std::cout << "Cant remove: file doest not exists" << std::endl;
          return false;
     }

     bool is_removed = std::filesystem::remove(filename_); // удаляем файл

     if (is_removed) // если файл удалился, то
     {
          if (response == responseToObservers::notification_on)
          {
               update(); // оповещаем наблюдателей
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
     notify(*this); // вызываем метод, определенный в базовом классе Subject для оповещения наблюдателей
}

customFile::customFile()
     : filename_ { }
     , file_  { }
{
}