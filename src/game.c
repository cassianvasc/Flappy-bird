//-------------------------------------------------------------------
#include "game.h"
#include "bird.h"
#include "pipe.h"
#include "linked_list.h"
#include "raylib.h"           // bibliotecas e demais arquivos
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
//--------------------------------------------------------------------
//                          variaveis globais
bool game_over = false;//flag de game over

float TIME_CREATION_CURRENT;//tempo atual de criaçao de canos

Bird* bird;

Texture2D bird_texture; //textura do passaro
Texture2D background; // textura do cenario

// Lista encadeada de tubos
Node* pipe_head;
Node* pipe_tail;

int passed; // contator de canos ultrapassados

float pipe_time; // tempo de criação de novos canos
//----------------------------------------------------------------------------
//funçao para gerar canos com buracos aleatorios
Pipe* generate_random_pipe(){
    int y = rand() % (int)(HEIGHT - PIPE_HOLE_HEIGHT); //cria a posiçao do buraco no cano, a funçao rand() gera um inteiro aleatorio. % faz com que  o resultado fique entre 0 e o numero calculado 
    return Pipe_create(WIDTH, y, PIPE_HOLE_HEIGHT); // retorna a criaçao de um novo cano, que sera gerado sempre no canto direito da tela e com o buraco aleatorio calculado anteriormente
}
//----------------------------------------------------------------------------
void Game_load(){
    game_over = false;

    TIME_CREATION_CURRENT = TIME_CRATION_PIPE;

    pipe_time = 0;

    bird = Bird_create(BIRD_X, BIRD_START_Y);
    bird_texture = LoadTexture("assets/sprites/bird.png");
    background = LoadTexture("assets/sprites/flappy_bird_background.png");

    Pipe* pipe = generate_random_pipe();
    add_end(&pipe_head, &pipe_tail, pipe);

    passed = 0;
}
//----------------------------------------------------------------------------
void Game_unload(){
    Bird_free(bird);
    UnloadTexture(bird_texture);

    while (pipe_head != NULL){
        remove_first(&pipe_head, &pipe_tail);
    }
}
//----------------------------------------------------------------------------
float pipe_time = 0.0f;
//----------------------------------------------------------------------------
void Game_update(){
    if (game_over) {
        if (IsKeyPressed(KEY_ENTER)) {
            Game_unload();
            screen = MENU;
            menu_load();
        }
        return;
    }
    pipe_time += GetFrameTime();
    
    TIME_CREATION_CURRENT -= GetFrameTime() * 0.05f;
    if (TIME_CREATION_CURRENT < 0.7f)
        TIME_CREATION_CURRENT = 0.7f;

    if (IsKeyPressed(KEY_SPACE)){
        Bird_jump(bird);
    }
    Bird_update(bird);

    if (pipe_time > TIME_CREATION_CURRENT){
        pipe_time = 0;
        Pipe* pipe = generate_random_pipe();
        add_end(&pipe_head, &pipe_tail, pipe);
    }

    if (pipe_head){
        Pipe* first_pipe = pipe_head->pipe;
        if (first_pipe->x < -PIPE_WIDTH){
            remove_first(&pipe_head, &pipe_tail);
        }
        if (first_pipe->passed == false && first_pipe->x + PIPE_WIDTH < BIRD_X - BIRD_RADIUS / 2){
            first_pipe->passed = true;
            passed++;
        }
    }

Rectangle birdRect = Bird_get_rect(bird);

Node *node = pipe_head;
while (node != NULL) {
    Pipe *p = node->pipe;

    Rectangle topRect, bottomRect;
    Pipe_get_rects(p, &topRect, &bottomRect);

    if (CheckCollisionRecs(birdRect, topRect) || CheckCollisionRecs(birdRect, bottomRect)) {
        game_over = true;
        return;
    }

    node = node->next;
}
    
    apply_function(&pipe_head, &pipe_tail, Pipe_update);
}

void Game_draw(){
    DrawTexturePro(
        background,
        (Rectangle){0, 0, background.width, background.height},
        (Rectangle){0, 0, WIDTH, HEIGHT},
        (Vector2){0, 0},
        0,
        WHITE
    );

    Bird_draw(bird, bird_texture);

    apply_function(&pipe_head, &pipe_tail, Pipe_draw);

    Node* cur = pipe_head;
    int length = 0;
    while(cur){
        length++;
        cur = cur->next;
    }

    char text[100];
    sprintf(text, "Tubos: %d\nPassados: %d", length, passed);
    DrawText(text, 100, 100, 40, BLACK);

    if (game_over) {
    const char *msg = "GAME OVER";
    const char *msg2 = "Pressione ENTER para reiniciar";

    int font1 = 80;
    int font2 = 30;

    DrawText(
        msg,
        WIDTH/2 - MeasureText(msg, font1)/2,
        HEIGHT/2 - 100,
        font1,
        RED
    );
    DrawText(
        msg2,
        WIDTH/2 - MeasureText(msg2, font2)/2,
        HEIGHT/2,
        font2,
        DARKGRAY
    );
}

}