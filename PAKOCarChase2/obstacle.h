#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class Obstacle
{
private:
	sf::RectangleShape model;
	sf::Vector2f size=sf::Vector2f(120,120);
	sf::Vector2f pos = sf::Vector2f(450,450);
public:
	Obstacle();
	sf::RectangleShape& getObstacle();
	void whenPlayerMove(sf::Vector2f _pos);
	void regenarateObstacle();
};

