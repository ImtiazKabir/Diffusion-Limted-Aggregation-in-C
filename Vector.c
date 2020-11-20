#include <stdlib.h>
#include "Vector.h"
#include <math.h>

Vector *createVector(float x, float y) {
    Vector *v = (Vector *) malloc(sizeof(Vector));
    v->x = x;
    v->y = y;
    return v;
}

void Vector_add(Vector *a, Vector *b) {
    a->x += b->x;
    a->y += b->y;
}

void Vector_sub(Vector *a, Vector *b) {
    a->x -= b->x;
    a->y -= b->y;
}

void Vector_mult(Vector *a, float m) {
    a->x *= m;
    a->y *= m;
}

void Vector_div(Vector *a, float m) {
    a->x /= m;
    a->y /= m;
}

double Vector_mag(Vector *a) {
    return hypot(a->x, a->y);
}

void Vector_normalized(Vector *a) {
    Vector_div(a, Vector_mag(a));
}

float Vector_dot(Vector *a, Vector *b) {
    return a->x * b->x + a->y * b->y;
}
