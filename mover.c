#include "mover.h"
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Vector.h"
#include "global.h"
#include <stdio.h>

Mover *createMover(float x, float y) {
    Mover *m = (Mover *) malloc(sizeof(Mover));
    m->loc = createVector(x, y);
    m->r = 5.0;
    m->speed = 3.0;
    m->canMove = true;
    return m;
}


void Mover_update(Mover *mover) {
    float x = rand() / (double) RAND_MAX - 0.5;
    float y = rand() / (double) RAND_MAX - 0.5;
    Vector *vel = createVector(x, y);
    Vector_normalized(vel);
    Vector_mult(vel, mover->speed);
    Vector_add(mover->loc, vel);
    free(vel);
    
    if (mover->loc->x < 0) mover->loc->x = 0;
    else if (mover->loc->x > WIDTH) mover->loc->x = WIDTH;
    if (mover->loc->y < 0) mover->loc->y = 0;
    else if (mover->loc->y > HEIGHT) mover->loc->y = HEIGHT;

    
}




void Mover_display(Mover *m) {
    al_draw_filled_circle(m->loc->x, m->loc->y, m->r, al_map_rgb(200, 0, 0));
    al_draw_circle(m->loc->x, m->loc->y, m->r, al_map_rgb(0, 0, 0), 1.0);
}

