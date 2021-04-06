#ifndef PARTICLES_H
#define PARTICLES_H

#define PI 3.14159265359
#define DEG_TO_RAD(x) (x * PI / 180)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "transform.h"
#include "display.h"

typedef struct particleEmitter
{
    int speed;
    Transform* emitter_transform;
} ParticleEmitter;


typedef struct particles
{
    int particle_duration;
    Transform* particle_transform;
    SDL_Rect* particle_box;
    SDL_Texture* particle_texture;
    /* ponteiro pro emissor criador */
    ParticleEmitter* emitterCreator;
} Particles;

ParticleEmitter* createParticleEmitter(int x, int y, int speed);
Particles* createParticle(ParticleEmitter* particleEmitter);
void moveParticles(Particles* particles);
void renderParticles(Particles* particles);
void destroyParticles(Particles* particles);
#endif