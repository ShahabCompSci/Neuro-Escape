#pragma once
#include <SDL.h>
#include "Player.hpp"
#include "Wall.hpp"
#include "Guard.hpp"
#include "Key.hpp"
#include "Door.hpp"
#include <vector>

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() const;
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    Player* player;
    std::vector<Wall> walls;
    std::vector<Guard> guards;
    // New game elements:
    bool keyCollected;
    bool gameWon;
    Uint32 startTime;
    Key* key;
    Door* door;
    int windowWidth;
    int windowHeight;
};
