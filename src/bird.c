#include "bird.h"
#include <stdlib.h>

void Bird_jump(Bird* bird){
    bird->vel_y = -BIRD_JUMP_FORCE;
}

void Bird_update(Bird* bird){
    bird->vel_y += GRAVITY;
    bird->pos_y += bird->vel_y;
}

void Bird_draw(Bird* bird, Texture2D bird_texture){
    int x = bird->pos_x - BIRD_RADIUS / 2;
    int y = bird->pos_y - BIRD_RADIUS / 2;

    float rotation = bird->vel_y < 0 ? -30 : 0;

    DrawTexturePro(
        bird_texture, 
        (Rectangle){0, 0, bird_texture.width, bird_texture.height},
        (Rectangle){x, y, BIRD_RADIUS, BIRD_RADIUS},
        (Vector2){BIRD_RADIUS / 2, BIRD_RADIUS / 2},
        rotation,
        WHITE
    );

    //DrawCircle(bird->pos_x, bird->pos_y, BIRD_RADIUS, YELLOW);
}

Bird* Bird_create(int x, int y){
    Bird* bird = malloc(sizeof(Bird));
    bird->pos_x = x;
    bird->pos_y = y;
    bird->vel_y = 0;
    return bird;
}

void Bird_free(Bird* bird){
    free(bird);
}

Rectangle Bird_get_rect(Bird *bird) {

    float hitbox_w = BIRD_RADIUS * 0.3f;
    float hitbox_h = BIRD_RADIUS * 0.6f;

    return (Rectangle){
        bird->pos_x - hitbox_w / 2,
        bird->pos_y - hitbox_h / 2,
        hitbox_w,
        hitbox_h
    };
}
