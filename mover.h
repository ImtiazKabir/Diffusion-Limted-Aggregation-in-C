#ifndef MOVER_H
#define MOVER_H

#include "Vector.h"
#include <stdbool.h>

typedef struct {
    Vector *loc;
    float r;
    bool canMove;
    float speed;
}Mover;

Mover *createMover(float, float);
void Mover_update(Mover *);
void Mover_display(Mover *);


#endif
