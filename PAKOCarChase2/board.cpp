#include "board.h"

Board::Board(std::string _tex) {
	tex.loadFromFile(_tex);
	background.setTexture(tex);
	background.setScale(1.5,1.5);
}

sf::Sprite& Board::getMap() {
	return background;
}

sf::Vector2u Board::getBorder() {
	return tex.getSize();
}

sf::Vector2f Board::getPos() {
	return background.getPosition();
}