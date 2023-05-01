#include "ai.h"
#include <iostream>

Ai::Ai(std::string _tex, sf::Vector2u _border) : Car(_tex, _border)
{
    pos.x = rand() % 1500;
    pos.y = rand() % 1500;
    x = pos.x;
    y = pos.y;
    model.setPosition(pos);
    sensor_pos = sf::Vector2f(pos.x, pos.y - 60);
    sensor.setPosition(sensor_pos);
}

void Ai::whenPlayerMove(sf::Vector2f _pos) {
	model.setPosition(_pos + pos);
}


void Ai::update(sf::Sprite& map, Obstacle*& obs) {    
    /*if (!sensor.getGlobalBounds().intersects(map.getGlobalBounds()))
    {
        Right = 1;
    }*/
    moving(map, obs);
    pos.x = x;
    pos.y = y;
}

void Ai::onAi(sf::Vector2f player_pos) {
    float dx = player_pos.x - model.getPosition().x;
    float dy = player_pos.y - model.getPosition().y;

    float distance = sqrt(dx * dx + dy * dy);
    //std::cout << distance << std::endl;

    if (distance > 200)
    {
        float rotation = atan2(dy, dx) * 180 / 3.141592; // konwersja radianów na stopnie

        if ((int)(angle * 180 / 3.141592) != (int)rotation && stop)
        {
            angle = rotation;
            if (angle > 360)
            {
                angle -= 360;
            }
            else if (angle < 0) {
                angle += 360;
            }
            //std::cout << (int)angle << std::endl;
        }
        if (!stop)
        {
            angle += 30;
            x -= 20;
            y -= 20;
            stop = 1;
        }
        model.setRotation(angle * 180 / 3.141592);
    }
    else {
        stop = 0;
    }
}

void Ai::restart() {
    pos.x = rand() % 1500;
    pos.y = rand() % 1500;
    x = pos.x;
    y = pos.y;
    model.setPosition(pos);
    sensor_pos = sf::Vector2f(pos.x, pos.y - 60);
    sensor.setPosition(sensor_pos);
}