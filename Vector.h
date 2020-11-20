#ifndef VECTOR_H
#define VECTOR_H

struct Vector {
    float x;
    float y;
};

typedef struct Vector Vector;

Vector *createVector(float, float);
void Vector_add(Vector *, Vector *);
void Vector_sub(Vector *, Vector *);
void Vector_mult(Vector *, float);
void Vector_div(Vector *, float);
double Vector_mag(Vector *);
void Vector_normalized(Vector *);
float Vector_dot(Vector *, Vector *);

#endif