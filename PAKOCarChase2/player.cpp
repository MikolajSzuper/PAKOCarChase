#include "player.h"

Player::Player(std::string _tex, sf::Vector2f pos, sf::Vector2u _border) : Car(_tex, _border)
{
	model.setPosition(pos);
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
    Right = 0;
    Left = 0;
    Down = 1;

}

sf::Vector2f Player::getPos() {
    model.setPosition(x - offsetX, y - offsetY);
    return sf::Vector2f(-offsetX, -offsetY);
}
