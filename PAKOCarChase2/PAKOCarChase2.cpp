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
    srand(time(NULL));
    Obstacle obs[10];
    int j = 0;
    while (j<10)
    {
        int k = 1 + j;
        while (k<10)
        {
            if (obs[j].getObstacle().getGlobalBounds().intersects(obs[k].getObstacle().getGlobalBounds()) || obs[j].getObstacle().getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())) {
                obs[j].regenarateObstacle();
            }
            else {
                k++;
            }
        }
        j++;
    }


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

        bool contact = 0;
        for (int i = 0; i < 10; i++) if (!contact) contact = player.Contact(obs[i].getObstacle());
        if (contact) player.stop = 0; else player.stop = 1;
        for (int i = 0; i < 10; i++)
        {
            obs[i].whenPlayerMove(map.getPos());
        }

        //Draw//
        app.clear(Color::White);
        map.whenPlayerMove(player.getPos());
        app.draw(map.getMap());


        for (int i = 0; i < 10; i++)
        {
            app.draw(obs[i].getObstacle());
        }

        app.draw(player.getPlayer());
        app.display();
    }

    return EXIT_SUCCESS;
}