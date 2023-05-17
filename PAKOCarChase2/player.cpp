#include "player.h"

std::map<std::string, int> Dir{ {"RIGHT", 0}, {"LEFT", 1} };

Player::Player(std::string _tex,sf::Vector2f pos, sf::Vector2u _border, sf::Vector2f scale) : Car(_tex, _border, scale)
{
	model.setPosition(pos);
    //sensor.setRadius(10);
    sensor_pos = sf::Vector2f(pos.x, pos.y - 60);
    sensor.setPosition(sensor_pos);
    x = 320;
    y = 240;
    turnSpeed = 0.07;
}

void Player::update(sf::Sprite& map, Obstacle*& obs, sf::View& view) {
    mps = map.getGlobalBounds();
    moving(map, obs);
    model.setRotation(angle * 180 / 3.141592);
    /*float pos_x = view.getCenter().x;
    float pos_y = view.getCenter().y;*/
    /*if (model.getPosition().x > 340 && model.getPosition().x < 1475)
    {
        pos_x = model.getPosition().x;
    }
    if (model.getPosition().y > 240 && model.getPosition().y < 1550) {
        pos_y = model.getPosition().y;
    }*/
    float pos_x = model.getPosition().x;
    float pos_y = model.getPosition().y;
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
    move();
}

void Player::move(std::string dir) {
    stop = 0;
    switch (Dir[dir])
    {
    case 0:
        Right = 1;
        break;
    case 1:
        Left = 1;
        break;
    }
    if (sensor.getGlobalBounds().intersects(mps) && !contact && model.getGlobalBounds().intersects(mps))
    {
        x += sin(prev_angle) * 4;
        y -= cos(prev_angle) * 4;
    }
}
void Player::move() {
    stop = 1;
}