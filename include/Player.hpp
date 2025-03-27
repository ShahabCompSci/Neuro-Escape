#pragma once
#include <SDL.h>
#include <vector>
#include "Wall.hpp"

class Player {
public:
    Player(int x, int y, int w, int h, int speed);
    void handleInput(const SDL_Event& event);
    void update(const std::vector<Wall>& walls);
    void render(SDL_Renderer* renderer);
    const SDL_Rect& getRect() const;
private:
    SDL_Rect rect;
    int speed;
    int velX, velY;
};
