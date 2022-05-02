/// file_observer.h представлен класс наблюдателя файла

#pragma once
#ifndef INCLUDE_FILE_OBSERVER_H
#define INCLUDE_FILE_OBSERVER_H

#include <observer_iface.h>
#include <string>
#include <chrono>

/// @brief класс наблюдателя файла

class FileObserver : public IObserver
{

public:

     /// @brief конструктор
     FileObserver();

     /// @brief коллбек при получении оповещения со стороны файла
     /// при его модификации
     /// проверяет на существование, изменение файла
     /// выводит в stdout валидность файла, размер и последнее изменение файла
     /// с префиксом [OBSERVER]
     /// @param file наблюдаемый объект-файл
     void onNotify(const Subject& file) override;

private:

     /// @brief получить время последних изменений в файле
     /// @param path путь к файлу
     /// @return время изменения файла
     std::time_t get_modified_time(const std::string& path);

     /// @brief зафиксировать текущее время в изменение файла
     /// @param modified_time текущее время
     void set_modified_time(std::time_t modified_time);

     /// @brief пребразование времени в формат Www Mmm dd hh:mm:ss yyyy\n
     /// @param time - время
     /// @return строка Www Mmm dd hh:mm:ss yyyy\n
     std::string serialize(std::time_t time);

private:

     /// последнее изменение файла
     std::time_t last_modified_time_;
};

#endif