//arquivo para definir as variaveis globais do codigo
#ifndef COMMON_H
#define COMMON_H

typedef enum {
    MENU,
    GAME
} SCREEN;

//gravidade
extern const float GRAVITY;

//bird
extern const float BIRD_RADIUS;
extern const float BIRD_X;
extern float BIRD_START_Y;
extern const float BIRD_JUMP_FORCE;

//pipe
extern const float PIPE_WIDTH;
extern float PIPE_VELOCITY;
extern float PIPE_HOLE_HEIGHT;

extern float TIME_CRATION_PIPE;

extern float WIDTH;
extern float HEIGHT;

extern SCREEN screen;

#endif