#include <custom_file.h>
#include <file_observer.h>
#include <random>
#include <chrono>
#include <memory>
#include <thread>
#include <iostream>

/// функция генерации строки
/// @return генерируемая строка
// данная функция используется для записи в файл сгенерированной строки
std::string get_random_string()
{
     std::srand(std::time(nullptr));
     auto lenght = std::rand()%20 + 1;
     std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
     std::random_device rd;
     std::mt19937 generator(rd());
     std::shuffle(str.begin(), str.end(), generator);
     return str.substr(0, lenght);
}

int main(int argc, char** argv) try
{
     // достаточно запустить скрипт start_build.sh, который собирает проект
     // и запускает исполняемый файл observer
     // возможные входные параметра:
     // название файла над которым будет производиться тестирование
     // если такой параметр не задан, то в корневой папке проекта будет создан
     // файл с именем test_default.txt

     const std::string filepath = argc == 2 ? argv[1] : "../test_default.txt";
     std::cout << "File name:\t" << filepath << std::endl;

     // Проверяем работает ли наблюдатель
     auto test1 = [&]()
     {
          // Создание объекта для взаимодействия с файлом
          customFile file(filepath, std::ios_base::out); // filepath – имя файла

          // Создание наблюдателя над файлом
          auto observer = std::make_unique<FileObserver>();

          // Добавление наблюдателя в список подписчиков на объект file
          file.addObserver(observer.get());

          // Закрытие файла -> отправляется оповещение наблюдателю
          file.closeFile();
     };

     // Проверяем работает ли удаление из списка
     auto test2 = [&]()
     {
          // Создание объекта для взаимодействия с файлом
          customFile file(filepath, std::ios_base::out); // filepath – имя файла

          // Создание наблюдателя над файлом
          auto observer = std::make_unique<FileObserver>();

          // Добавление наблюдателя в список подписчиков на объект file
          file.addObserver(observer.get());

          // Удаление из списка наблюдателя
          file.removeObserver(observer.get());

          // Закрытие файла и сохранение состояние файла -> отправляется оповещение наблюдателю
          file.closeFile();
     };

     // Проверяем работает ли оповещение для двух и более наблюдателей
     auto test3 = [&]()
     {
          // Создание объекта для взаимодействия с файлом
          customFile file(filepath, std::ios_base::out); // filepath – имя файла

          // Создание первого наблюдателя над файлом
          auto observer_first = std::make_unique<FileObserver>();

          // Создание второго наблюдателя над файлом
          auto observer_second = std::make_unique<FileObserver>();

          // Добавление первого наблюдателя в список подписчиков на объект file
          file.addObserver(observer_first.get());

          // Добавление второго наблюдателя в список подписчиков на объект file
          file.addObserver(observer_second.get());

          // Закрытие файла и сохранение состояние файла -> отправляется оповещение наблюдателям
          file.closeFile();
     };

     // Перезапись данных в файл
     auto test4 = [&]()
     {
          // Создание объекта для взаимодействия с файлом
          customFile file(filepath, std::ios_base::out); // filepath – имя файла

          // Создание наблюдателя над файлом
          auto observer = std::make_unique<FileObserver>();

          // Добавление наблюдателя в список подписчиков на объект file
          file.addObserver(observer.get());

          // Перезапись в файл рандомно сгенерированной строки,
          // отправляется оповещение наблюдателю
          file.writeToFile(get_random_string());

          // Закрытие файл и сохранение состояние -> отправляется оповещение наблюдателю
          file.closeFile();

     };

     // Запись данных в конец имеющегося файла
     auto test5 = [&]()
     {
          // Создание объекта для взаимодействия с файлом
          customFile file(filepath, std::ios_base::out); // filepath – имя файла

          // Создание наблюдателя над файлом
          auto observer = std::make_unique<FileObserver>();

          // Добавление наблюдателя в список подписчиков на объект file
          file.addObserver(observer.get());

          // Перезапись в файл рандомно сгенерированной строки
          file.writeToFile(get_random_string(), std::ios_base::out,
               customFile::responseToObservers::notification_off);

          // Сохранение состояние файла
          file.closeFile(customFile::responseToObservers::notification_off);

          // Запись данных в конец имеющегося файла,
          // отправляется оповещение наблюдателю
          file.writeToFile(get_random_string(), std::ios_base::app);

          // Закрытие файл и сохранение состояние -> отправляется оповещение наблюдателю
          file.closeFile();
     };

     // Удаление существующего файла
     auto test6 = [&]()
     {
          // Создание объекта для взаимодействия с файлом
          customFile file(filepath, std::ios_base::out); // filepath – имя файла

          // Создание наблюдателя над файлом
          auto observer = std::make_unique<FileObserver>();

          // Добавление наблюдателя в список подписчиков на объект file
          file.addObserver(observer.get());

          // Удаление файла
          file.removeFile();
     };

     //test1(); // запуск 1-го теста
     //test2(); // запуск 2-го теста
     //test3(); // запуск 3-го теста
     //test4(); // запуск 4-го теста
     //test5(); // запуск 5-го теста
     test6(); // запуск 6-го теста
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