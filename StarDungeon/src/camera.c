#include "camera.h"

Camera* createCamera(int x, int y, int width, int height){

    Camera* c = (Camera*)malloc(sizeof(Camera));
    c->camera_transform = (Transform*)malloc(sizeof(Transform));
    c->camera_transform->x = x;
    c->camera_transform->y = y;
    c->camera_transform->w = width;
    c->camera_transform->h = height;

    c->attached_transform = NULL;

    return c;

}

void moveCamera(Camera* camera, SDL_Rect* rBG, Transform* transform){

    camera->camera_transform->x = transform->x;
    camera->camera_transform->y = transform->y;


}