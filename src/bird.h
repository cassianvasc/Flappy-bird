// arquivo .h (header) para permitir que o arquivo bird.c se comunique com os demais
#ifndef BIRD_H
#define BIRD_H

#include "raylib.h"
#include "common.h"

typedef struct { //struct p definir as caracteristicas do passaro
    float pos_x;
    float pos_y;

    float vel_y;
} Bird;

void Bird_jump(Bird* bird);

void Bird_update(Bird* bird); //no arquivo .h apenas chamo a funçao, que esta definida no arquivo .c
void Bird_draw(Bird* bird, Texture2D bird_texture);

Bird* Bird_create(int x, int y);
void Bird_free(Bird* bird);
Rectangle Bird_get_rect(Bird *bird);


#endif