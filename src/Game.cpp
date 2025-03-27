#include "Game.hpp"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Window Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    isRunning = true;
    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

void Game::update() {
    // Game logic goes here (placeholder)
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black background
    SDL_RenderClear(renderer);
    // Rendering goes here (placeholder)
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::running() const {
    return isRunning;
}
