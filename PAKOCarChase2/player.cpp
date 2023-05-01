#include "player.h"

Player::Player(std::string _tex,sf::Vector2f pos, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(pos);
    //sensor.setRadius(10);
    sensor_pos = sf::Vector2f(pos.x, pos.y - 60);
    sensor.setPosition(sensor_pos);
    x = 320;
    y = 240;
}

void Player::update(sf::Sprite& map, Obstacle*& obs) {
    moving(map, obs);
    model.setRotation(angle * 180 / 3.141592);
    if (x > 320 && x < 1475) offsetX = x - 320;
    if (y > 240 && y < 1550) offsetY = y - 240;
}

sf::Vector2f Player::getPos() {
    model.setPosition(x - offsetX, y - offsetY);
    return sf::Vector2f(-offsetX, -offsetY);
}

sf::Vector2f Player::getPosToPolice() {
    return model.getPosition();
}

bool Player::Collison(Ai other) {
    if (model.getGlobalBounds().intersects(other.getPlayer().getGlobalBounds())) {
        return 1;
    }
    return 0;
}

void Player::restart() {
    sf::Vector2f pos(320,240);
    model.setPosition(pos);
    //sensor.setRadius(10);
    sensor_pos = sf::Vector2f(pos.x, pos.y - 60);
    sensor.setPosition(sensor_pos);
    offsetX = 0;
    offsetY = 0;
    x = 320;
    y = 240;
}