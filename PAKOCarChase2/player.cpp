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

void Player::update(sf::Sprite& map, Obstacle*& obs, sf::View& view) {
    moving(map, obs);
    model.setRotation(angle * 180 / 3.141592);
    float pos_x = view.getCenter().x;
    float pos_y = view.getCenter().y;
    if (model.getPosition().x > 340 && model.getPosition().x < 1475)
    {
        pos_x = model.getPosition().x;
    }
    if (model.getPosition().y > 240 && model.getPosition().y < 1550) {
        pos_y = model.getPosition().y;
    }
    view.setCenter(sf::Vector2f(pos_x,pos_y));
    model.setPosition(x, y);
}

sf::Vector2f Player::getPos() {
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
    x = 320;
    y = 240;
}