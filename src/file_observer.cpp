#include <file_observer.h>
#include <custom_file.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <filesystem>

// коллбек при получении оповещения со стороны наблюдаемого объекта
void FileObserver::onNotify(const Subject& file)
{
     // используем std::filesystem (C++17) для получения
     // необходимой информации о состоянии текущего файла
     namespace fs = std::filesystem;

     // можем кастить, т.к. мы знаем над каким типом мы наблюдаем
     auto&& file_ =  static_cast<const customFile&> (file);

     const std::string filename = file_.getFilename();
     if (fs::exists(filename)) // если файл не существует, то он был удален, иначе:
     {

          // получаем время последнего изменения над файлом:
          const std::time_t current_modified_time = get_modified_time(filename);
          if (!last_modified_time_) // если время последнего изменения над файлом не было зафиксировано, то
          {
               set_modified_time(current_modified_time); // фиксируем время
          }

          if (fs::is_empty(filename)) // если файл пуст, значит он был только создан:
          {
               std::cout << "[OBSERVER] : " << "The file was empty but" << std::endl;
               std::cout << "\thas been created. Time:\t" << serialize(current_modified_time) << std::endl;
               return;
          }

          // если файл не был пуст:
          // начальное сообщение для вывода:
          std::string to_out_ {"[OBSERVER] : The file exists.\nLast modified time:\t" + serialize(last_modified_time_)};

          // если фиксированное время в прошлый раз не равно времени последнего изменения над файлом,
          // то произошли изменения над файлом
          if (current_modified_time != last_modified_time_)
          {
               // обновляем сообщение о том, что файл быз изменен
               to_out_ = "[OBSERVER] : The file has been changed.\nCurrent modified time:\t" + serialize(current_modified_time)
                         + "Last modified time:\t" + serialize(last_modified_time_);
               // фиксируем время
               set_modified_time(current_modified_time);
          }
          // выводим сообщение и размер файла
          std::cout << to_out_ << "Size:\t" << fs::file_size(filename) << std::endl;
          return;
     }
     // выводим сообщение о том, что файл был изменен
     std::cout << "[OBSERVER] : " << "The file was removed!" << std::endl;
     last_modified_time_ = std::time_t{0}; // обнуляем время
}

std::time_t FileObserver::get_modified_time(const std::string& path)
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
     return std::asctime(std::localtime(&time)); // пребразование времени в формат Www Mmm dd hh:mm:ss yyyy\n
}

FileObserver::FileObserver()
     : last_modified_time_ { 0 } // по умолчанию последнее изменение файла равно 0
{

}