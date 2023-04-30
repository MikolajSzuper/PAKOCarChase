#include <SFML/Graphics.hpp>
#include <iostream>
#include "car.h"
#include "player.h"
#include "board.h"
#include "obstacle.h"
#include "ai.h"
#include "button.h"

using namespace sf;

RenderWindow app(VideoMode(640, 480), "Pako Car Game");
void NewGame();

int main()
{    
    app.setFramerateLimit(60);

    sf::Sprite logo;
    sf::Texture tex_logo;
    tex_logo.loadFromFile("assets/logo.png");
    logo.setTexture(tex_logo);
    logo.setOrigin(193,96.5);
    logo.setPosition(sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)-125));
    logo.scale(0.6,0.6);

    Button buttonPlay(app, "Play", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)));
    Button buttonWhoBest(app, "Records", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)+50));
    Button buttonExit(app, "Exit", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2) + 100));
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed) {
                app.close();
            }
        }

        app.clear(sf::Color(80, 80, 80));
        buttonPlay.update(app);
        buttonWhoBest.update(app);
        buttonExit.update(app);
        app.draw(logo);
        app.display();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (buttonPlay.isHover()) {
                NewGame();
            }
            else if (buttonWhoBest.isHover())
            {
                std::cout << "Records!" << std::endl;
            }
            else if(buttonExit.isHover())
            {
                return EXIT_SUCCESS;
            }
        }

    }
    return EXIT_SUCCESS;
}

void NewGame() {
    Board map("assets/grass.png");
    Player player("assets/car.png", Vector2f(app.getSize().x / 2, app.getSize().y / 2), map.getBorder());
    Ai player1("assets/police.png", map.getBorder());
    srand(time(NULL));
    Obstacle obs[10];
    int j = 0;
    while (j < 10)
    {
        int k = 1 + j;
        while (k < 10)
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

    sf::Clock clock;
    int s=0, m=0;

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

        Obstacle* wsk_obs = *&obs;


        for (int i = 0; i < 10; i++)
        {
            obs[i].whenPlayerMove(map.getPos());
        }

        player1.whenPlayerMove(map.getPos());


        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 1.f)
        {
            player1.onAi(player.getPosToPolice());
            // Inkrementacja licznika
            s++;
            // Zerowanie czasu licznika
            clock.restart();
        }
        std::string win_status;
        if (s>59)
        {
            s = 0;
            m++;
        }
        win_status = std::to_string(m) + ":" + std::to_string(s);

        sf::Font font;
        font.loadFromFile("assets/ROMAN SHINE.ttf");
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setPosition(10.0f, 10.0f);
        text.setString("Time: " + win_status);

        player.update(map.getMap(), wsk_obs);

        player1.update(map.getMap(), wsk_obs);

        //Draw//
        app.clear(Color::White);
        map.whenPlayerMove(player.getPos());
        app.draw(map.getMap());


        for (int i = 0; i < 10; i++)
        {
            app.draw(obs[i].getObstacle());
        }

        app.draw(player.getPlayer());
        app.draw(player1.getPlayer());
        //app.draw(player.getSensor());
        app.draw(text);
        app.display();
    }
}