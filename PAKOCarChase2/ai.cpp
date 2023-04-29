#include "ai.h"
#include <iostream>

Ai::Ai(std::string _tex, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(pos);
    sensor_pos = sf::Vector2f(pos.x, pos.y - 60);
    sensor.setPosition(sensor_pos);
    x = pos.x;
    y = pos.y;
}

void Ai::whenPlayerMove(sf::Vector2f _pos) {
	model.setPosition(_pos + pos);
}


void Ai::update(sf::Sprite& map, Obstacle*& obs, sf::Vector2f player_pos) {

    float dx = player_pos.x - model.getPosition().x;
    float dy = player_pos.y - model.getPosition().y;

    float distance = sqrt(dx * dx + dy * dy);

        if (distance > 10)
        {
            float rotation = atan2(dy, dx) * 180 / 3.141592; // konwersja radianów na stopnie

            if (angle != rotation || !(angle > rotation - 60 && angle < rotation + 60))
            {
                angle = rotation;
                stop = 1;
            }
        }
        else {
            stop = 0;
        }

    

    if (!sensor.getGlobalBounds().intersects(map.getGlobalBounds()))
    {
        Right = 1;
    }
    moving(map, obs);
    pos.x = x;
    pos.y = y;
}
