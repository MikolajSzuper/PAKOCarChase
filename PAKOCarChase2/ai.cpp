#include "ai.h"
#include <iostream>

Ai::Ai(std::string _tex, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(pos);
    x = pos.x;
    y = pos.y;
}

void Ai::whenPlayerMove(sf::Vector2f _pos) {
	model.setPosition(_pos + pos);
}

void Ai::update() {
    moving();
    pos.x = x;
    pos.y = y;
}
