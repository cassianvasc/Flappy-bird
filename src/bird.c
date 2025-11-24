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
    float scale = BIRD_RADIUS / (float)bird_texture.width;
    float w = BIRD_RADIUS;
    float h = bird_texture.height * scale;

    DrawTexturePro(
        bird_texture,
        (Rectangle){0, 0, bird_texture.width, bird_texture.height},
        (Rectangle){bird->pos_x, bird->pos_y, w, h},
        (Vector2){w/2, h/2},
        bird->vel_y < 0 ? -30 : 0,
        WHITE
    );
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

    float hitbox_w = BIRD_RADIUS * 0.9f;
    float hitbox_h = BIRD_RADIUS * 0.85f;


    return (Rectangle){
        bird->pos_x - hitbox_w / 2,
        bird->pos_y - hitbox_h / 2,
        hitbox_w,
        hitbox_h
    };
}
