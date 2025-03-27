#include "Game.hpp"

int main(int argc, char* argv[]) {
    Game game;
    if (!game.init("NeuroEscape", 800, 600)) {
        return -1;
    }

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
        SDL_Delay(16); // ~60 FPS
    }

    return 0;
}
