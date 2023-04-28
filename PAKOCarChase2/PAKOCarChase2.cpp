#include <SFML/Graphics.hpp>
#include <iostream>
#include "car.h"
#include "board.h"
#include "obstacle.h"

using namespace sf;
int main()
{
    RenderWindow app(VideoMode(640, 480), "Pako Car Game");
    app.setFramerateLimit(60);
    Board map("assets/grass.png");
    Car player("assets/car.png",Vector2f(app.getSize().x/2, app.getSize().y/2), map.getBorder());

    Obstacle obs;


    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed) {
                app.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) player.move("RIGHT");
        if (Keyboard::isKeyPressed(Keyboard::Left)) player.move("LEFT");
        if (Keyboard::isKeyPressed(Keyboard::Space)) player.Stop();

        player.update();

        player.Contact(obs.getObstacle());
        obs.whenPlayerMove(map.getPos());

        //Draw//
        app.clear(Color::White);
        map.whenPlayerMove(player.getPos());
        app.draw(map.getMap());

        app.draw(obs.getObstacle());

        app.draw(player.getPlayer());
        app.display();
    }

    return EXIT_SUCCESS;
}