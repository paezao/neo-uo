#include "texture.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>

struct texture * load_texture(void *data, uint32 width, uint32 height)
{
    struct texture * texture = (struct texture *)malloc(sizeof(struct texture));
    texture->id = 0;
    texture->width = width;
    texture->height = height;

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, 
            GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char *)data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void unload_texture(struct texture *texture)
{
    if(texture->id)
    {
        glDeleteTextures(1, &texture->id);
    }
    free(texture);
}
