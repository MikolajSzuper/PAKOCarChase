#include "car.h"

Car::Car(std::string _tex, sf::Vector2u _border, sf::Vector2f scale) {
    tex.loadFromFile(_tex);
    model.setTexture(tex);
    model.setScale(scale.x*0.5, scale.y*0.5);
    maxSpeed = maxSpeed+((maxSpeed / 3) * scale.x*scale.x);
    model.setOrigin(46, 80);//99.5//36
    border = _border;
    _scale = scale;
    sensor.setSize(sf::Vector2f(40, 50));
    sensor.setOrigin(sensor.getSize().x / 2, sensor.getSize().y / 2);
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
    if (sensor.getGlobalBounds().intersects(bump) || model.getGlobalBounds().intersects(obj.getGlobalBounds())) return 1;
    return 0;
}

void Car::moving(sf::Sprite& map, Obstacle*& obs) {


    if (speed < maxSpeed)
        if (speed < 0) speed += dec;
        else speed += acc;


    if (Right && speed != 0) angle += turnSpeed * speed / maxSpeed;
    if (Left && speed != 0) angle -= turnSpeed * speed / maxSpeed;

    contact = 0;
    for (int i = 0; i < 10; i++) {
        if (!contact) {
            contact = Contact(obs[i].getObstacle());
        }
        if (contact) { 
            speed = 4; 
        }
        else {
            if (!(Right == 0 && Left == 0))
            {
                x += sin(angle) * 0.3;
                y -= cos(angle) * 0.3;
            }
        }
    }

    if (stop && sensor.getGlobalBounds().intersects(map.getGlobalBounds()) && model.getGlobalBounds().intersects(map.getGlobalBounds())) {
        x += sin(angle) * speed;
        y -= cos(angle) * speed;
        prev_angle = angle;
    }
    if (!(sensor.getGlobalBounds().intersects(map.getGlobalBounds()))){
        x -= sin(angle) * speed;
        y += cos(angle) * speed;
        prev_angle = angle;
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