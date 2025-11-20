#include "pipe.h"
#include <stdlib.h>

void Pipe_update(Pipe* pipe){
    pipe->x -= PIPE_VELOCITY;
}

void Pipe_draw(Pipe* pipe){
    // Tubo de cima
    DrawRectangle(pipe->x, 0, PIPE_WIDTH, pipe->hole_start_y, GREEN);

    // Tubo de baixo
    int y = pipe->hole_start_y + pipe->hole_size;
    DrawRectangle(pipe->x, y, PIPE_WIDTH, HEIGHT - y, GREEN);
}

Pipe* Pipe_create(float x, float hole_start_y, float hole_size){
    Pipe* pipe = malloc(sizeof(Pipe));
    pipe->x = x;
    pipe->hole_start_y = hole_start_y;
    pipe->hole_size = hole_size;
    pipe->passed = false;

    return pipe;
}

void Pipe_free(Pipe* pipe){
    free(pipe);
}
void Pipe_get_rects(Pipe *pipe, Rectangle *top, Rectangle *bottom) {
    // Retângulo do pipe de cima
    *top = (Rectangle){
        pipe->x,
        0,
        PIPE_WIDTH,
        pipe->hole_start_y
    };

    // Retângulo do pipe de baixo
    float y = pipe->hole_start_y + pipe->hole_size;
    *bottom = (Rectangle){
        pipe->x,
        y,
        PIPE_WIDTH,
        HEIGHT - y
    };
}
