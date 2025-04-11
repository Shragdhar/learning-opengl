#include "FileHandler.hpp"

namespace FileHandler
{
    std::string get_base_dir()
    {
        std::string current_path = std::filesystem::current_path();
        std::string proj_dir = std::string(current_path) + "/../";
        return proj_dir;
    }

    std::string read(std::string path, std::string base_dir)
    {
        if (base_dir.empty()) {
            std::cout << "Empty path provided, using default one";
            base_dir = FileHandler::get_base_dir();
        }

        std::filesystem::path checked_path = path;
        std::string absolute_path;

        if (checked_path.is_relative()) {
            absolute_path = base_dir + path;
        }
        else if (checked_path.is_absolute()) {
            absolute_path = path;
        }

        std::fstream file(absolute_path);
        if (!file) { std::cout << "Couldn't read file: " << std::endl; return ""; }

        std::string file_content((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

        file.close();

        return file_content;
    }

    void write(std::string path, std::string content, std::string base_dir)
    {
        if (base_dir.empty()) {
            std::cout << "Empty path provided, using default one";
            base_dir = FileHandler::get_base_dir();
        }

        std::filesystem::path checked_path = path;
        std::string absolute_path;

        if (checked_path.is_relative()) {
            absolute_path = base_dir + path;
        }
        else if (checked_path.is_absolute()) {
            absolute_path = path;
        }

        std::fstream file;

        file.open(absolute_path, std::ios_base::out);
        if (!file) { 
            std::cout << "File failed to create: " << std::endl;
            return;
        }

        file << content;
        file.close();
    }
}
