#pragma once
#include "car.h"
#include "obstacle.h"
class Ai : public Car
{
private:
	sf::Vector2f pos;
public:
	Ai(std::string _tex, sf::Vector2u _border);
	void getPos();
	void update(sf::Sprite& map, Obstacle*& obs);
	void onAi(sf::Vector2f player_pos);
	void restart();
};

