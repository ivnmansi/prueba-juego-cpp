#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "inc/Game.h"

int main(int argc, char** argv){

    srand(time(NULL));

    Game* game = Game::getInstance();
    if (!game->init()) {
        printf("Error: Failed to initialize game\n");
        return -1;
    }

    game->run();
    game->shutdown();

    return 0;
}