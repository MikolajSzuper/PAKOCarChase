#include "car.h"

std::map<std::string, int> Dir{ {"RIGHT", 0}, {"LEFT", 1} };

Car::Car(std::string _tex, sf::Vector2u _border) {
    tex.loadFromFile(_tex);
    model.setTexture(tex);
    model.setScale(0.5, 0.5);
    model.setOrigin(46, 80);//99.5//36
    border = _border;
}

void Car::update() {
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

void Car::move(std::string dir) {
    switch (Dir[dir])
    {
    case 0:
        Right = 1;
        break;
    case 1:
        Left = 1;
        break;
    }
}

sf::Sprite& Car::getPlayer() {
    return model;
}

sf::Vector2f Car::getPos() {
    model.setPosition(x-offsetX,y-offsetY);
    return sf::Vector2f(-offsetX, -offsetY);
}

void Car::Stop() {
    if (stop) stop = 0; else stop = 1;
}

bool Car::Contact(sf::Sprite& obj) {
    sf::FloatRect bump;
    bump = obj.getGlobalBounds();
    bump.width = bump.width - 5;
    bump.height = bump.height - 5;
    if (model.getGlobalBounds().intersects(bump)) return 1;
    return 0;
}