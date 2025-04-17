#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include "includes/stb_image.h"

namespace FileHandler
{
// File Handling
    std::string get_base_dir();
    std::string read(std::string path, std::string base_dir = "");
    void        write(std::string path, std::string content, std::string base_dir = "");
}

class Image
{
public:
    Image(std::string image);
    typedef unsigned char uchar;

    void status() const;
    void free_memory();
    int get_width() const     {return width;}
    int get_height() const    {return height;}
    uchar* get_data() const   {return image_data;}

private:
    int width, height, nrChannels;
    uchar* image_data;
};
