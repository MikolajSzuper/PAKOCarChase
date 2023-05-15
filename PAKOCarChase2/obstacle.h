#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class Obstacle
{
private:
	sf::Texture tex;
	sf::Sprite model;
	sf::Vector2f size=sf::Vector2f(120,120);
	sf::Vector2f pos = sf::Vector2f(450,450);
public:
	Obstacle();
	sf::Sprite& getObstacle();
	void regenarateObstacle();
};

