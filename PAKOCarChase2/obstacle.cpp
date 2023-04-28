#include "obstacle.h"

Obstacle::Obstacle() {
	model.setSize(size);
	model.setFillColor(sf::Color::Yellow);
	model.setPosition(pos);
}

sf::RectangleShape Obstacle::getObstacle() {
	return model;
}

void Obstacle::whenPlayerMove(sf::Vector2f _pos) {
	model.setPosition(_pos + pos);
	//std::cout << pos.x <<" "<<pos.y << std::endl;
}