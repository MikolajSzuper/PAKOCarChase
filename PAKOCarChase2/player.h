#pragma once
#include "car.h"
class Player : public Car
{
public:
	Player(std::string _tex, sf::Vector2f pos, sf::Vector2u _border);
};

