#pragma once
#include "car.h"
#include "obstacle.h"
#include "ai.h"
class Player : public Car
{
private:
	float offsetX = 0, offsetY = 0;
public:
	Player(std::string _tex, sf::Vector2f pos, sf::Vector2u _border);
	void update(sf::Sprite& map, Obstacle*& obs);
	sf::Vector2f getPos();
	sf::Vector2f getPosToPolice();
	bool Collison(Ai other);
	void restart();
};

