#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Board
{
private:
	sf::Texture tex;
	sf::Sprite background;
public:
	Board(std::string _tex);
	sf::Sprite& getMap();
	sf::Vector2u getBorder();
	sf::Vector2f getPos();
};

