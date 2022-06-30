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
std::string shuffle_string()
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
     const std::string filepath = argc == 2 ? argv[1] : "../default.txt";
     std::cout << "File name:\t" << filepath << std::endl;

     customFile file(filepath, std::ios_base::out);
     auto observer = std::make_unique<FileObserver>();
     file.addObserver(observer.get());

     auto helper_output = []()
     {
          std::cout << "The following values for testing:\n"
               << "1 - to open file with out open mode (it resets the data)" << std::endl
               << "2 - to write random generate string to file (it resets the data)" << std::endl
               << "3 - to write random generate string to end of file (it does not reset the data)" << std::endl
               << "4 - to remove file" << std::endl
               << "5 - get file name" << std::endl
               << "6 - to quit" << std::endl;
     };

     while (true)
     {
          helper_output();
          int value_{};
          while( !(std::cin >> value_) ) // ожидаем только число
          {
               std::cin.clear(); // очищаем флаг для последующего чтения
               while (std::cin.get() != '\n')
               {
                    continue;
               }
               std::cout << "Please enter valid value. Manual:" << std::endl;
               helper_output();
          }

          switch (value_)
          {
               case 1 :
               {
                    std::cout << "Case 1 : opening file with out open mode" << std::endl;
                    file.openFile(filepath);
                    std::cout << "...closing file to save state" << std::endl;
                    file.closeFile();
                    std::cout << "--------------END OF CASE 1--------------\n";
                    break;
               }
               case 2:
               {
                    std::string to_write_ = shuffle_string();
                    std::cout << "Case 2 : writing random generate string to file (it resets the data)\t"
                         << "String to be written: " << to_write_ << std::endl;
                    file.writeToFile(to_write_);
                    std::cout << "...closing file to save state" << std::endl;
                    file.closeFile();
                    std::cout << "--------------END OF CASE 2--------------\n";
                    break;
               }
               case 3:
               {
                    std::string to_write_ = shuffle_string();
                    std::cout << "Case 3 : writing random generate string to end of file (it does not reset the data)\t"
                         << "String to be written: " << to_write_ << std::endl;
                    file.writeToFile(to_write_, std::ios_base::app);
                    std::cout << "...closing file to save state" << std::endl;
                    file.closeFile();
                    std::cout << "--------------END OF CASE 3--------------\n";

                    break;
               }
               case 4:
               {
                    std::cout << "Case 4: \nremoving file\n";
                    file.removeFile();
                    std::cout << "--------------END OF CASE 4--------------\n";
                    break;
               }
               case 5:
               {
                    std::cout <<"Case 5: getting file name" << std::endl;
                    std::cout << filepath << std::endl;
                    std::cout << "--------------END OF CASE 5--------------\n";
                    break;
               }
               case 6:
               {
                    std::cout << "Case 6: quiting a programm..." << std::endl;
                    return EXIT_SUCCESS;
               }
               default:
                    helper_output();
          }
          std::cout << "_____________________________\n\n";
          std::this_thread::sleep_for(std::chrono::seconds(5)); // интервал ввода 5 секунд
     }
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