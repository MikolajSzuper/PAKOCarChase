#include "car.h"

std::map<std::string, int> Dir{ {"RIGHT", 0}, {"LEFT", 1} };

Car::Car(std::string _tex, sf::Vector2u _border) {
    tex.loadFromFile(_tex);
    model.setTexture(tex);
    model.setScale(0.5, 0.5);
    model.setOrigin(46, 80);//99.5//36
    border = _border;

    sensor.setSize(sf::Vector2f(40, 50));
    sensor.setOrigin(sensor.getSize().x / 2, sensor.getSize().y / 2);
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

void Car::moving(sf::Sprite& map, Obstacle*& obs) {

    bool contact = 0;
    for (int i = 0; i < 10; i++) if (!contact) contact = Contact(obs[i].getObstacle());
    if (contact) stop = 0; else stop = 1;

    if (speed < maxSpeed)
        if (speed < 0) speed += dec;
        else speed += acc;


    if (Right && speed != 0) angle += turnSpeed * speed / maxSpeed;
    if (Left && speed != 0) angle -= turnSpeed * speed / maxSpeed;


    if (stop && sensor.getGlobalBounds().intersects(map.getGlobalBounds())) {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
    }
    //model.setRotation(angle * 180 / 3.141592);
    //Sensor
    const double rad = 3.14 / 180.0;
    float circleX = model.getPosition().x + 40 * sin(model.getRotation() * rad);
    float circleY = model.getPosition().y - 40 * cos(model.getRotation() * rad);
    sf::Vector2f circlePosition(circleX, circleY);
    sensor.setPosition(circlePosition);
    sensor.setRotation(model.getRotation() - 90);
    Right = 0;
    Left = 0;
    Down = 1;
}

sf::RectangleShape& Car::getSensor() {
    return sensor;
}