#include "text.h"

Texts::Texts(std::string txt, sf::Vector2f pos)
{
	font.loadFromFile("assets/ROMAN SHINE.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getCharacterSize() / 2);
    text.setPosition(pos);
    text.setString(txt);
}
Texts::Texts(std::string txt, sf::Vector2f pos, int size)
{
    font.loadFromFile("assets/ROMAN SHINE.ttf");
    text.setFont(font);
    text.setCharacterSize(size);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getCharacterSize() / 2);
    text.setPosition(pos);
    text.setString(txt);
}

void Texts::update(sf::RenderWindow& window)
{
	window.draw(text);
}

void Texts::update(sf::RenderWindow& window, std::string txt, sf::Vector2f pos)
{
    text.setString(txt);
    text.setPosition(pos);
    window.draw(text);
}
