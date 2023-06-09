#include "text.h"

Texts::Texts(std::string txt, sf::Vector2f pos)
{
	font.loadFromFile("assets/ROMAN SHINE.ttf");
    text.setFont(font);
    text.setCharacterSize(32);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(pos);
    text.setString(txt);
}
Texts::Texts(std::string txt, sf::Vector2f pos, int size)
{
    font.loadFromFile("assets/ROMAN SHINE.ttf");
    text.setFont(font);
    text.setCharacterSize(size);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(pos);
    text.setString(txt);
}

void Texts::update(sf::RenderWindow& window, sf::Vector2f pos)
{
    text.setPosition(pos);
	window.draw(text);
}

void Texts::update(sf::RenderWindow& window, std::string txt, sf::Vector2f pos)
{
    text.setString(txt);
    text.setPosition(pos);
    window.draw(text);
}
