#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
class Texts
{
private:
    sf::Font font;
    sf::Text text;
public:
    Texts(std::string txt,sf::Vector2f pos);
    Texts(std::string txt, sf::Vector2f pos, int size);
    void update(sf::RenderWindow& window, sf::Vector2f pos);
    void update(sf::RenderWindow& window, std::string txt, sf::Vector2f pos);
};

