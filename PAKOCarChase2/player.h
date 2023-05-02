#pragma once
#include "car.h"
#include "obstacle.h"
#include "ai.h"
class Player : public Car
{
public:
	Player(std::string _tex, sf::Vector2f pos, sf::Vector2u _border);
	void update(sf::Sprite& map, Obstacle*& obs, sf::View& view);
	sf::Vector2f getPos();
	bool Collison(Ai other);
	void restart();
};

