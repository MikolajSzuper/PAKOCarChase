#include "obstacle.h"

Obstacle::Obstacle() {
	tex.loadFromFile("assets/obstacle.png");
	model.setTexture(tex);
	model.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	model.setScale(0.2,0.2);
	pos.x = rand() % 1500;
	pos.y = rand() % 1500;
	model.setPosition(pos);
}

sf::Sprite& Obstacle::getObstacle() {
	return model;
}

void Obstacle::whenPlayerMove(sf::Vector2f _pos) {
	model.setPosition(_pos + pos);
	//std::cout << pos.x <<" "<<pos.y << std::endl;
}

void Obstacle::regenarateObstacle()
{
	pos.x = rand() % 1500;
	pos.y = rand() % 1500;
	model.setPosition(pos);
}
