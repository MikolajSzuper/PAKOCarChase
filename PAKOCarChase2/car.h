#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"


class Car
{
protected:
    sf::Texture tex;
    sf::Sprite model;
    sf::Vector2u border;
    float speed = 0, angle = 0;
    float maxSpeed = 6.0;
    float acc = 0.2, dec = 0.3;
    float turnSpeed = 0.1;
    bool Down = 0, Right = 0, Left = 0;
public:
    bool stop = 1;
    Car(std::string _tex, sf::Vector2u _border);
    void move(std::string);
    sf::Sprite& getPlayer();
    void Stop();
    bool Contact(sf::Sprite& obj);
};