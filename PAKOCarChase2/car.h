#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "obstacle.h"


class Car
{
protected:
    sf::RectangleShape sensor;
    sf::Texture tex;
    sf::Sprite model;
    sf::Vector2u border;
    sf::Vector2f sensor_pos;
    sf::Vector2f _scale;
    float x, y;
    float prev_angle;
    float speed = 0, angle = 0;
    float maxSpeed = 6.0;
    double acc = 0.2, dec = 0.3;
    double turnSpeed = 0.1;
    bool Down = 0, Right = 0, Left = 0;
    bool contact;
public:
    bool stop = 1;
    Car(std::string _tex, sf::Vector2u _border, sf::Vector2f scale);
    sf::Sprite& getPlayer();
    void Stop();
    bool Contact(sf::Sprite& obj);
    void moving(sf::Sprite& map, Obstacle*& obs);
    sf::RectangleShape& getSensor();
};
