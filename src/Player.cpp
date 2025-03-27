#include "Player.hpp"
#include "CircleUtils.hpp"

Player::Player(int x, int y, int w, int h, int speed)
    : rect{x, y, w, h}, speed(speed), velX(0), velY(0) {}

void Player::handleInput(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_w: velY = -speed; break;
            case SDLK_s: velY = speed; break;
            case SDLK_a: velX = -speed; break;
            case SDLK_d: velX = speed; break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
            case SDLK_s: velY = 0; break;
            case SDLK_a:
            case SDLK_d: velX = 0; break;
        }
    }
}

void Player::update(const std::vector<Wall>& walls) {
    SDL_Rect nextPos = rect;
    nextPos.x += velX;
    nextPos.y += velY;

    for (const Wall& wall : walls) {
        if (SDL_HasIntersection(&nextPos, &wall.getRect())) {
            return; // cancel movement if colliding
        }
    }
    rect = nextPos;
}

void Player::render(SDL_Renderer* renderer) {
    int centerX = rect.x + rect.w / 2;
    int centerY = rect.y + rect.h / 2;
    int radius = rect.w / 2;

    // Outer black circle (outline)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawFilledCircle(renderer, centerX, centerY, radius);

    // Inner green face
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    drawFilledCircle(renderer, centerX, centerY, radius - 2);

    // Eyes
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect leftEye = { rect.x + 10, rect.y + 12, 5, 5 };
    SDL_Rect rightEye = { rect.x + 30, rect.y + 12, 5, 5 };
    SDL_RenderFillRect(renderer, &leftEye);
    SDL_RenderFillRect(renderer, &rightEye);

    // Smile
    SDL_Rect smile = { rect.x + 12, rect.y + 30, 25, 3 };
    SDL_RenderFillRect(renderer, &smile);

    // Tongue
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect tongue = { rect.x + 24, rect.y + 34, 6, 5 };
    SDL_RenderFillRect(renderer, &tongue);
}

const SDL_Rect& Player::getRect() const {
    return rect;
}
