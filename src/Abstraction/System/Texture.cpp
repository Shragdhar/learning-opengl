#include <glad/glad.h>
#include "Texture.hpp"

Texture::Texture(const Image& image)
{
    instance_id = texture_count++;

    if (!image.get_data()) { std::cout << "No image found"; }
    /*else { std::cout << "found image with status: "; }*/

    glGenTextures(1, &texture_id);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

#ifdef DEBUG_TEST
    std::cout << "\033[31m [Texture_C]\033[0m image.get_data(): " << static_cast<void*>(image.get_data()) << "\n";
#endif

    if (image.get_data()) {

#ifdef DEBUG_TEST
        image.status();
#endif
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.get_width(), image.get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.get_data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + instance_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}
