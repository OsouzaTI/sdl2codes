#ifndef TRANSFORM_H
#define TRANSFORM_H

typedef struct transform
{
    float x;
    float y;
    int   w;
    int   h;
    float scale_x;
    float scale_y;
    int direction;
} Transform;


#endif