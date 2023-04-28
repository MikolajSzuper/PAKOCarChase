#pragma once
#include "car.h"
class Player : public Car
{
private:
	float x = 320, y = 240;
	float offsetX = 0, offsetY = 0;
public:
	Player(std::string _tex, sf::Vector2f pos, sf::Vector2u _border);
	void update();
	sf::Vector2f getPos();
	sf::CircleShape& getSensor();
};

