#include "texture.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

Texture * load_texture(void *data, uint32 width, uint32 height)
{
    Texture * texture = (Texture *)malloc(sizeof(Texture));
    texture->id = 0;
    texture->width = width;
    texture->height = height;

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, 
            GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *)data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void unload_texture(Texture *texture)
{
    if(texture->id)
    {
        glDeleteTextures(1, &texture->id);
    }
    free(texture);
}
