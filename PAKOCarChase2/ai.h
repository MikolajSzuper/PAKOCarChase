#pragma once
#include "car.h"
class Ai : public Car
{
private:
	sf::Vector2f pos = sf::Vector2f(100, 1000);
public:
	Ai(std::string _tex, sf::Vector2u _border);
	void whenPlayerMove(sf::Vector2f _pos);
	void getPos();
	void update();
};

