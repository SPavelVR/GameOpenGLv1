
#ifndef __TEXTURE_H
#define __TEXTURE_H 1

#include <string_t.h>

#include <stdint.h>

typedef struct {
    uint32_t id;
    int width;
    int height;
} Texture;

Texture* init_texture(String nameTexture);
void free_texture(Texture* texture);

void bind_texture(Texture* Texture);

#endif