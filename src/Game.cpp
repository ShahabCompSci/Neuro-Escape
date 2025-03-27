#include "Game.hpp"
#include "CircleUtils.hpp"
#include <iostream>
#include <cmath>
#include <SDL.h>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), player(nullptr),
    keyCollected(false), gameWon(false), key(nullptr), door(nullptr) {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    windowWidth = width;
    windowHeight = height;
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

    // Create player (positioned at 100,100, size 50x50, speed 5)
    player = new Player(100, 100, 50, 50, 5);

    // Create maze walls
    walls.clear();
    // Outer boundaries
    walls.push_back(Wall(0, 0, windowWidth, 20)); // top
    walls.push_back(Wall(0, windowHeight - 20, windowWidth, 20)); // bottom
    walls.push_back(Wall(0, 0, 20, windowHeight)); // left
    walls.push_back(Wall(windowWidth - 20, 0, 20, windowHeight)); // right

    // Inner maze walls (example layout)
    walls.push_back(Wall(200, 100, 20, 400));
    walls.push_back(Wall(400, 200, 20, 400));
    walls.push_back(Wall(600, 50, 20, 500));
    walls.push_back(Wall(800, 300, 20, 400));
    walls.push_back(Wall(1000, 150, 20, 500));
    walls.push_back(Wall(1200, 250, 20, 400));

    // Create guard(s)
    guards.clear();
    guards.push_back(Guard(300, 500, 50, 50, 2, 150)); // patrol guard

    // Create key and door
    key = new Key(150, 800, 30, 30);
    door = new Door(windowWidth - 100, windowHeight / 2 - 50, 60, 100); // door near right edge

    keyCollected = false;
    gameWon = false;

    startTime = SDL_GetTicks();

    return true;
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        player->handleInput(event);
    }
}

void Game::update() {
    player->update(walls);

    // Check if player collects key
    if (!keyCollected && SDL_HasIntersection(&player->getRect(), &key->getRect())) {
        keyCollected = true;
        key->setCollected(true);
        door->unlock();
    }

    // Check if player reaches door and key is collected => win game
    if (keyCollected && SDL_HasIntersection(&player->getRect(), &door->getRect())) {
        gameWon = true;
        isRunning = false;
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You Escaped!",
            ("You escaped in " + std::to_string(elapsedTime / 1000.0) + " seconds.").c_str(), window);
    }

    // Update guards with chasing behavior
    for (auto& guard : guards) {
        int guardCenterX = guard.getRect().x + guard.getRect().w / 2;
        int guardCenterY = guard.getRect().y + guard.getRect().h / 2;
        int playerCenterX = player->getRect().x + player->getRect().w / 2;
        int playerCenterY = player->getRect().y + player->getRect().h / 2;
        int dx = playerCenterX - guardCenterX;
        int dy = playerCenterY - guardCenterY;
        float distance = std::sqrt(dx * dx + dy * dy);
        if (distance < 300) {
            guard.chase(playerCenterX, playerCenterY);
        } else {
            guard.update();
        }
        // Collision check with player -> game over
        if (SDL_HasIntersection(&guard.getRect(), &player->getRect())) {
            isRunning = false;
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Caught!", "You've been caught by a guard!", window);
        }
    }
}

void Game::render() {
    // Render background checkerboard tiles
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int tileSize = 50;
    for (int y = 0; y < windowHeight; y += tileSize) {
        for (int x = 0; x < windowWidth; x += tileSize) {
            bool isDark = ((x / tileSize) + (y / tileSize)) % 2 == 0;
            if (isDark) {
                SDL_SetRenderDrawColor(renderer, 204, 204, 0, 255); // dark yellow
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 255, 102, 255); // light yellow
            }
            SDL_Rect tile = { x, y, tileSize, tileSize };
            SDL_RenderFillRect(renderer, &tile);
        }
    }

    // Render walls
    for (const auto& wall : walls) {
        wall.render(renderer);
    }
    // Render key and door
    key->render(renderer);
    door->render(renderer);

    // Render guards
    for (const auto& guard : guards) {
        guard.render(renderer);
    }
    // Render player
    player->render(renderer);

    // Render fog-of-war overlay
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect fogRect = { 0, 0, windowWidth, windowHeight };
    SDL_RenderFillRect(renderer, &fogRect);
    // Cut out player's vision
    int visionRadius = 150;
    int centerX = player->getRect().x + player->getRect().w / 2;
    int centerY = player->getRect().y + player->getRect().h / 2;
    drawFilledCircleAlpha(renderer, centerX, centerY, visionRadius, 0, 0, 0, 0);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    if (player) delete player;
    if (key) delete key;
    if (door) delete door;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::running() const {
    return isRunning;
}
