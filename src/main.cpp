#include <custom_file.h>
#include <file_observer.h>
#include <random>
#include <chrono>
#include <memory>
#include <thread>
#include <iostream>

int main(int argc, char** argv) try
{
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