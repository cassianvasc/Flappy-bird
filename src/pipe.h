#ifndef PIPE_H
#define PIPE_H

#include "raylib.h"
#include "common.h"

typedef struct {
    float x;
    float hole_start_y;
    float hole_size;
    bool passed;
} Pipe;

void Pipe_update(Pipe* pipe); //no arquivo .h apenas chamo a funçao, que esta definida no arquivo .c
void Pipe_draw(Pipe* pipe);

Pipe* Pipe_create(float x, float hole_start_y, float hole_size);
void Pipe_free(Pipe* pipe);
void Pipe_get_rects(Pipe *pipe, Rectangle *top, Rectangle *bottom);

#endif