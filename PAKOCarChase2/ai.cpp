#include "ai.h"

Ai::Ai(std::string _tex, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(sf::Vector2f(100, 100));
}
