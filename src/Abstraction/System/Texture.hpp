#pragma once
#include "Abstraction/System/Utils.hpp"
#include <sys/types.h>

class Texture
{
public:
    Texture(const Image& image);

    void bind();

    u_int get_id() { return texture_id; }

private:
    u_int texture_id;
    int instance_id;
    static inline u_int texture_count = 0;
};
