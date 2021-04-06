#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include "transform.h"
#include "display.h"

typedef struct camera
{
    Transform* camera_transform;

    Transform* attached_transform;
} Camera;

Camera* createCamera(int x, int y, int width, int height);
void moveCamera(Camera* camera, SDL_Rect* rBG, Transform* transform);

#endif