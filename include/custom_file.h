#ifndef INCLUDE_CUSTOM_FILE_H
#define INCLUDE_CUSTOM_FILE_H

#include <string>
#include <fstream>
#include <subject.h>

class customFile final : public Subject
{

public:

     customFile(const std::string& filename, std::ios::openmode openmode);

     void writeToFile(const std::string& text, std::ios::openmode openmode = std::ios::out);

     void closeFile();

     void openFile(const std::string& filename, std::ios::openmode openmode = std::ios::out);

     bool removeFile();

     std::string getFilename() const;

     ~customFile() override;

     void update();

private:

     std::string filename_;

     std::fstream file_;
};


#endif