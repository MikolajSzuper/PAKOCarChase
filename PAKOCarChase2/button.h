#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class Button
{
private:
	sf::Sprite shape;
	sf::Texture tex;
	sf::Text text;
	sf::Font font;
	bool hover=false;
public:
	Button(sf::RenderWindow& window,std::string txt,sf::Vector2f pos);
	void update(sf::RenderWindow& window, sf::Vector2f pos);
	bool isHover();
};

