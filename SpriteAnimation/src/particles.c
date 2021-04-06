#include "particles.h"

ParticleEmitter* createParticleEmitter(int x, int y, int speed){

    ParticleEmitter* p = (ParticleEmitter*)malloc(sizeof(ParticleEmitter));
    p->emitter_transform = (Transform*)malloc(sizeof(Transform));
    p->emitter_transform->x = x;
    p->emitter_transform->y = y;
    p->speed = speed;
    return p;

}

Particles* createParticle(ParticleEmitter* particleEmitter){

    SDL_Surface* particleSurface = NULL;

    Particles* p = (Particles*)malloc(sizeof(Particles));
    p->emitterCreator = particleEmitter; /* no criador */
    p->particle_box = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    p->particle_transform = (Transform*)malloc(sizeof(Transform));
    p->particle_transform->x = particleEmitter->emitter_transform->x;
    p->particle_transform->y = particleEmitter->emitter_transform->y;
    p->particle_transform->w = 32;
    p->particle_transform->h = 32;
    p->particle_transform->direction = rand()%100;
    p->particle_transform->scale_x = 3;
    p->particle_transform->scale_y = 3;
    p->particle_box->x = p->particle_transform->x;
    p->particle_box->y = p->particle_transform->y;
    p->particle_box->w = p->particle_transform->w * p->particle_transform->scale_x;
    p->particle_box->h = p->particle_transform->h * p->particle_transform->scale_y;
    p->particle_duration = 1;
    
    particleSurface = IMG_Load("F:\\Projects\\c\\SDL2\\SpriteAnimation\\assets\\img\\leave02.png");
    if(!particleSurface){
        printf("nao foi possivel criar particleSurface\n");
        return NULL;
    }

    p->particle_texture = SDL_CreateTextureFromSurface(renderer, particleSurface);
    SDL_FreeSurface(particleSurface);

    return p;

}

void destroyParticles(Particles* particles){

    /* emitter creator */
    free(particles->emitterCreator->emitter_transform);
    free(particles->emitterCreator);
    
    free(particles->particle_transform);
    free(particles->particle_box);
    free(particles);

}

void moveParticles(Particles* particles){
    int deg = DEG_TO_RAD(SDL_GetTicks()/(particles->particle_transform->direction+10));
    int speed = particles->emitterCreator->speed;

    particles->particle_transform->x += speed * cos(deg) * deltaTime;
    particles->particle_transform->y += speed * deltaTime;

    if(particles->particle_transform->x > WINDOW_WIDTH || particles->particle_transform->y > WINDOW_HEIGHT){
        particles->particle_transform->x =  particles->emitterCreator->emitter_transform->x;
        particles->particle_transform->y =  particles->emitterCreator->emitter_transform->y;
    }

}

void renderParticles(Particles* particles){

    particles->particle_box->x = particles->particle_transform->x;
    particles->particle_box->y = particles->particle_transform->y;

    SDL_RenderCopyEx(
        renderer, particles->particle_texture,
        NULL, particles->particle_box,
        SDL_GetTicks()/30, NULL,
        SDL_FLIP_NONE
    );

}