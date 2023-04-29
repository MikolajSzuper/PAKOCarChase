#include "car.h"

std::map<std::string, int> Dir{ {"RIGHT", 0}, {"LEFT", 1} };

Car::Car(std::string _tex, sf::Vector2u _border) {
    tex.loadFromFile(_tex);
    model.setTexture(tex);
    model.setScale(0.5, 0.5);
    model.setOrigin(46, 80);//99.5//36
    border = _border;
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

void Car::Stop() {
    if (stop) stop = 0; else stop = 1;
}

bool Car::Contact(sf::Sprite& obj) {
    sf::FloatRect bump;
    bump = obj.getGlobalBounds();
    bump.width = bump.width - 5;
    bump.height = bump.height - 5;
    if (sensor.getGlobalBounds().intersects(bump)) return 1;
    return 0;
}

void Car::moving() {
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
    model.setRotation(angle * 180 / 3.141592);
    //Sensor
    const double rad = 3.14 / 180.0;
    float circleX = model.getPosition().x + 50 * sin(model.getRotation() * rad);
    float circleY = model.getPosition().y - 50 * cos(model.getRotation() * rad);
    sf::Vector2f circlePosition(circleX, circleY);
    sensor.setPosition(circlePosition);
    Right = 0;
    Left = 0;
    Down = 1;
}