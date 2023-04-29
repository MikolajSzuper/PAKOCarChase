#include "button.h"

Button::Button(sf::RenderWindow& window, std::string txt, sf::Vector2f pos)
{
	font.loadFromFile("assets/ROMAN SHINE.ttf");
	text.setFont(font);
	text.setString(txt);
	text.setOrigin(text.getGlobalBounds().width/2, text.getCharacterSize() / 2);
	//shape.setSize(sf::Vector2f(100, 50));
	tex.loadFromFile("assets/button.png");
	shape.setTexture(tex);
	shape.setScale(0.2,0.4);
	shape.setOrigin(688 / 2, 61 / 2);
	shape.setPosition(pos);
	text.setPosition(shape.getPosition().x,shape.getPosition().y - 10);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color(90,255,130));
	shape.setColor(sf::Color(255,70,70));
	//shape.setFillColor(sf::Color::Yellow);
	window.draw(shape);
	window.draw(text);
}

void Button::update(sf::RenderWindow& window)
{
	sf::Mouse mouse;
	if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse.getPosition(window)))) {
		shape.setColor(sf::Color(255, 10, 10));
		text.setFillColor(sf::Color(0, 255, 70));
		hover = true;
	}
	else {
		hover = false;
		text.setFillColor(sf::Color(90, 255, 130));
		shape.setColor(sf::Color(255, 70, 70));
	}

	window.draw(shape);
	window.draw(text);
}

bool Button::isHover() {
	return hover;
}
