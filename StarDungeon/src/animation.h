#ifndef ANIMATION_H
#define ANIMATION_H

typedef struct animation
{
    float speed;
    int frames;
    int currentFrame;
    long int frameCount;
} Animation;

void resetFrameCount(Animation* animation);

#endif