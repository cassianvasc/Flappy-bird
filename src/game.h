#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

extern bool game_over;

void Game_load();
void Game_unload();

void Game_update();
void Game_draw();


#endif