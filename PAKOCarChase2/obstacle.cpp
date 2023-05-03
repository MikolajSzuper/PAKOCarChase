#include "obstacle.h"

Obstacle::Obstacle() {
	tex.loadFromFile("assets/oil.png");
	model.setTexture(tex);
	model.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	model.setScale(0.1,0.1);
	pos.x = rand() % 1500;
	pos.y = rand() % 1500;
	model.setPosition(pos);
}

sf::Sprite& Obstacle::getObstacle() {
	return model;
}

void Obstacle::regenarateObstacle()
{
	pos.x = rand() % 1500;
	pos.y = rand() % 1500;
	model.setPosition(pos);
}
