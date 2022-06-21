/// custom_file.h представлен класс для взаимодействия с файлом

#pragma once
#ifndef INCLUDE_CUSTOM_FILE_H
#define INCLUDE_CUSTOM_FILE_H

#include <string>
#include <fstream>
#include <subject.h>
#include <functional>

/// @brief класс для работы с файлом
/// реализован в виде паттерна Наблюдателя
class customFile final : public Subject
{

public:

     /// @brief вспомогательный класс customFile
     /// используется в функциях для включения и отключения коллбеков у наблюдателей
     /// по умолчанию notification_off
     enum class responseToObservers : int
     {
          notification_on,
          notification_off
     };

public:
     /// @brief конструктор по умолчанию
     customFile();

     /// @brief конструктор
     /// @param filename название файла ( path приветствуется )
     /// @param openmode флаг открытия файла
     /// @throw runtime_error если файл не смог открыться
     customFile(const std::string& filename, std::ios::openmode openmode);

     /// @brief запись в файл
     /// @param text данные, записываемые в файл
     /// @param response флаг коллбека
     /// @param openmode флаг открытия файла
     void writeToFile(
          const std::string& text,
          std::ios::openmode openmode = std::ios::out,
          responseToObservers response = responseToObservers::notification_on
     );

     /// @brief закрытие файла
     /// @param response флаг коллбека
     void closeFile(responseToObservers response = responseToObservers::notification_on);

     /// @brief открытие файла
     /// @param filename название файла ( path приветствуется )
     /// @param response флаг коллбека
     /// @param openmode флаг открытия файла
     void openFile(
          const std::string& filename,
          std::ios::openmode openmode = std::ios::out,
          responseToObservers response = responseToObservers::notification_on
     );

     /// @brief удаление файла
     /// @param response флаг коллбека
     /// @return true - если файл удалился, иначе - false
     bool removeFile(responseToObservers response = responseToObservers::notification_on);

     /// @brief получение имени файла
     /// @return имя файла
     std::string getFilename() const;

     /// @brief Деструктор
     ~customFile() override;

     /// @brief Обновление данных в файле
     /// оповещает наблюдателей
     void update();

private:

     /// имя файла
     std::string filename_;

     /// объект для манипулирования с файлами
     std::fstream file_;
};


#endif