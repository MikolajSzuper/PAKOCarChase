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
    if (model.getGlobalBounds().intersects(bump)) return 1;
    return 0;
}