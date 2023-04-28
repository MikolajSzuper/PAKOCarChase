#include "player.h"

Player::Player(std::string _tex, sf::Vector2f pos, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(pos);
    sensor.setRadius(10);
    sensor.setOrigin(5, 5);
    sensor_pos = sf::Vector2f(pos.x, pos.y - 60);
    sensor.setPosition(sensor_pos);
}

void Player::update() {
    if (speed < maxSpeed)
        if (speed < 0) speed += dec;
        else speed += acc;


    if (Right && speed != 0) angle += turnSpeed * speed / maxSpeed;
    if (Left && speed != 0) angle -= turnSpeed * speed / maxSpeed;

    if (stop && x + sin(angle) * speed > 0 && x + sin(angle) * speed < ((float)border.x + 550)) {
        x += sin(angle) * speed;
    }
    if (stop && y - cos(angle) * speed > 0 && y - cos(angle) * speed < ((float)border.y + 550)) {
        y -= cos(angle) * speed;
    }

    if (x > 320 && x < 1475) offsetX = x - 320;
    if (y > 240 && y < 1550) offsetY = y - 240;

    model.setRotation(angle * 180 / 3.141592);

    


    /*local x = sin(rad * angle) * length
    local y = 0
     local z = cos(rad * angle) * length*/

    float circleX = model.getPosition().x + 50* std::sin(angle);
    float circleY = model.getPosition().y - 50* std::cos(angle);

    /*float circleX = model.getPosition().x - 40 * std::cos(angle * 180 / 3.141592);
    float circleY = model.getPosition().y - 40 * std::sin(angle * 180 / 3.141592);*/
    sf::Vector2f circlePosition(circleX, circleY);
    sensor.setPosition(circlePosition);

    Right = 0;
    Left = 0;
    Down = 1;

}

sf::Vector2f Player::getPos() {

    model.setPosition(x - offsetX, y - offsetY);
    //sensor.setPosition(x - offsetX, y - 40 - offsetY);
    return sf::Vector2f(-offsetX, -offsetY);
}

sf::CircleShape& Player::getSensor() {
    return sensor;
}
