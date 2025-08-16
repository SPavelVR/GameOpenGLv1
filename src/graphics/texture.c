
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/texture.h"
#include "loadsys/loadTextures.h"

Texture* init_texture(String nameTexture) {
    return load_texture(nameTexture);
};

void free_texture(Texture* texture) {
    if (texture == NULL) return ;
    
    if (texture->id != 0)
        glDeleteTextures(1, &(texture->id));
    texture->id = 0;
    free(texture);
};

void bind_texture(Texture* texture) {
    if (texture == NULL || texture->id == 0) return ;

    glBindTexture(GL_TEXTURE_2D, texture->id);
};