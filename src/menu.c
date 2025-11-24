#include "menu.h"
#include "raylib.h"
#include "common.h"
#include "game.h"

static Texture2D menu_background = {0};
static bool menu_loaded = false;


void menu_load(){
    if (menu_loaded) return; // se o menu ja tiver carregado, retorna

    menu_background = LoadTexture("assets/sprites/flappy_bird_background.png");
    menu_loaded = true;
}


void menu_unload(){
    if (!menu_loaded) return;

    UnloadTexture(menu_background);
    menu_loaded = false;
}


void menu_update(){
    if(IsKeyPressed(KEY_ENTER)){
        Game_load();
        screen = GAME;
    }
}


void menu_draw(){
    DrawTexturePro(
        menu_background,
        (Rectangle){0, 0, menu_background.width, menu_background.height},
        (Rectangle){0, 0, WIDTH, HEIGHT},
        (Vector2){0, 0},
        0,
        WHITE
    );

    const char *title = "TIPO FLAPPY BIRD";
    int titlesize = 96;
    DrawText(
        title,
        WIDTH / 2 - MeasureText(title, titlesize)/2,
        HEIGHT * 0.25f,
        titlesize,
        BLACK
    );

    const char *instr = "Pressione ENTER para jogar";
    int instrsize = 28;
    DrawText(
        instr,
        WIDTH / 2 - MeasureText(instr, instrsize) / 2,
        HEIGHT * 0.6f,
        instrsize,
        DARKGRAY
    );
}