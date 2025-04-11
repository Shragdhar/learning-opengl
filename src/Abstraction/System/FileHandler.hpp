#include <iostream>
#include <filesystem>
#include <fstream>

namespace FileHandler
{
// File Handling
    std::string get_base_dir();
    std::string read(std::string path, std::string base_dir = "");
    void        write(std::string path, std::string content, std::string base_dir = "");
}
