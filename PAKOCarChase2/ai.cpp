#include "ai.h"
#include <iostream>

Ai::Ai(std::string _tex, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(pos);
}

void Ai::whenPlayerMove(sf::Vector2f _pos) {
	model.setPosition(_pos + pos);
}

void Ai::update() {
    if (speed < maxSpeed)
        if (speed < 0) speed += dec;
        else speed += acc;

    if (Right && speed != 0) angle += turnSpeed * speed / maxSpeed;
    if (Left && speed != 0) angle -= turnSpeed * speed / maxSpeed;

    if (stop && x + sin(angle) * speed > 0 && x + sin(angle) * speed < ((float)border.x + 550)) {
        x += sin(angle) * speed;
    }
    if (stop && y - cos(angle) * speed > 0 && y - cos(angle) * speed < ((float)border.y + 550)) {
        y -= cos(angle) * speed;
    }
    model.setRotation(angle * 180 / 3.141592);
    Right = 0;
    Left = 0;
    Down = 1;
    pos.x = x;
    pos.y = y;
}
