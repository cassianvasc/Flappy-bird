#include "raylib.h"
#include "common.h"
#include "game.h"

const float GRAVITY = 0.15f;
const float BIRD_RADIUS = 100.0f;
const float BIRD_X = 250.0f;
const float BIRD_JUMP_FORCE = 8.0f;
float BIRD_START_Y = 400;

const float PIPE_WIDTH = 150.0f;
float PIPE_VELOCITY = 3.0f;
float PIPE_HOLE_HEIGHT = 300.0f;

float TIME_CRATION_PIPE = 4.0f;

float WIDTH = 800;
float HEIGHT = 600;

SCREEN screen = GAME;

int main(void) {
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Flappy Bird"); //funçao da raylib para iniciar e ajustar a tela ao monitor
    SetTargetFPS(60);

    WIDTH = GetScreenWidth();
    HEIGHT = GetScreenHeight();

    BIRD_START_Y = HEIGHT / 2;

    Game_load();
    // Menu_load();

    while (!WindowShouldClose()) { //tudo que aparece na tela é escrito dentro dessa funçao da raylib
        if (screen == GAME){
            Game_update();
        } else if (screen == MENU) {
            //Menu_update();
        }

        BeginDrawing();
        if (screen == GAME){
            Game_draw();
        } else if (screen == MENU) {
            //Menu_draw();
        }
        EndDrawing();
    }

    Game_unload();
    // Menu_unload();
    CloseWindow();
    return 0;
}
