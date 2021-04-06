cmake_minimum_required (VERSION 3.8)
project(SpaceInvaders)

# Add source to this project's executable.
set(sources
    "src/constants.h"
    "src/display.c"
    "src/display.h"
    "src/enemy.c"
    "src/enemy.h"
    "src/label.c"
    "src/label.h"
    "src/logs.c"
    "src/logs.h"
    "src/player.c"
    "src/player.h"
    "src/projectile.c"
    "src/projectile.h"
    "src/transform.h"
    "src/main.c"
)

add_executable(SpaceInvaders ${sources})
target_include_directories(SpaceInvaders PRIVATE deps)
target_link_directories(SpaceInvaders PRIVATE deps/SDL2/lib/x86  
                                         deps/SDL2_TTF/lib
                                         deps/SDL2_MIXER/lib
                                         deps/SDL2_IMAGE/lib
)

target_link_libraries(SpaceInvaders PRIVATE SDL2.lib                                     
                                     SDL2main.lib
                                     SDL2_ttf.lib                                     
                                     SDL2_mixer.lib                                     
                                     SDL2_image.lib  
)
# TODO: Add tests and install targets if needed.
