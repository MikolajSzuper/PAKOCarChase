#include "player.h"

Player::Player(std::string _tex, sf::Vector2f pos, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(pos);
}
