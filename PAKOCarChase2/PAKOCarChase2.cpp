#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "car.h"
#include "player.h"
#include "board.h"
#include "obstacle.h"
#include "ai.h"
#include "button.h"
#include "text.h"

using namespace sf;

RenderWindow app(VideoMode(640, 480), "Pako Car Game");
void GameOver(std::string record);
void NewGame();

int main()
{    
    app.setFramerateLimit(60);

    bool scoreboard = 0;
    sf::Sprite logo;
    sf::Texture tex_logo;
    tex_logo.loadFromFile("assets/logo.png");
    logo.setTexture(tex_logo);
    logo.setOrigin(193,96.5);
    logo.setPosition(sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)-125));
    logo.scale(0.6,0.6);

    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    app.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

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
                if (scoreboard)
                {

                }
                else {

                }
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
    srand(time(NULL));
    Board map("assets/grass.png");
    Player player("assets/car.png", Vector2f(app.getSize().x / 2, app.getSize().y / 2), map.getBorder());
    const int obs_how_many = 10;
    const int bots_how_many = 2;
    Obstacle obs[obs_how_many];
    Ai bots[bots_how_many] = {
        Ai("assets/police.png", map.getBorder()),
        Ai("assets/police.png", map.getBorder()),
    };
    sf::Clock clock;
    int s = 0, m = 0;
    int lose = 0;
    /*int j = 0;
    while (j < obs_how_many)
    {
        int k = 1 + j;
        while (k < obs_how_many)
        {
            if (obs[j].getObstacle().getGlobalBounds().intersects(obs[k].getObstacle().getGlobalBounds()) || obs[j].getObstacle().getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())) {
                obs[j].regenarateObstacle();
            }
            else {
                k++;
            }
        }
        j++;
    }*/

        while (app.isOpen())
        {
            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed) {
                    app.close();
                }
            }


            if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) player.move("RIGHT");
            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) player.move("LEFT");
            //if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::)) player.Stop();

            Obstacle* wsk_obs = *&obs;


            for (int i = 0; i < obs_how_many; i++)
            {
                obs[i].whenPlayerMove(map.getPos());
            }
            for (int i = 0; i < bots_how_many; i++)
            {
                if (player.Collison(bots[i])) {
                    lose = 1;
                }
                bots[i].whenPlayerMove(map.getPos());
                bots[i].update(map.getMap(), wsk_obs);
                //bots[i].onAi(player.getPosToPolice());
            }


            sf::Time elapsed = clock.getElapsedTime();
            if(elapsed.asSeconds() >= 0.5f) {
                for (int i = 0; i < bots_how_many; i++)
                {
                    bots[i].onAi(player.getPosToPolice());
                }
            }
            if (elapsed.asSeconds() >= 1.f)
            {
                /*for (int i = 0; i < bots_how_many; i++)
                {
                    bots[i].onAi(player.getPosToPolice());
                }*/
                s++;
                clock.restart();
            }
            //std::string win_status;
            std::stringstream win_status;
            if (s > 59)
            {
                s = 0;
                m++;
            }
            win_status << std::setfill('0') << std::setw(2) << m << ":" << std::setw(2) << s;
            //win_status = std::to_string(m) + ":" + std::to_string(s);

            sf::Font font;
            font.loadFromFile("assets/ROMAN SHINE.ttf");
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(24);
            text.setPosition(10.0f, 10.0f);
            text.setString("Time: " + win_status.str());

            player.update(map.getMap(), wsk_obs);


            //Draw//
            app.clear(Color::White);
            map.whenPlayerMove(player.getPos());
            app.draw(map.getMap());


            for (int i = 0; i < obs_how_many; i++)
            {
                app.draw(obs[i].getObstacle());
            }

            app.draw(player.getPlayer());
            for (int i = 0; i < bots_how_many; i++)
            {
                app.draw(bots[i].getPlayer());
            }
            //app.draw(player.getSensor());
            app.draw(text);
            app.display();
            if (lose) {
                GameOver(win_status.str());
                player.restart();
                map.whenPlayerMove(player.getPos());
                lose = 0;
                m = 0;
                s = 0;
                for (int i = 0; i < bots_how_many; i++)
                {
                    bots[i].restart();
                }
                for (int i = 0; i < obs_how_many; i++)
                {
                    obs[i].regenarateObstacle();
                }
            }
    }
}

void GameOver(std::string record) {
    Texts text("Game Over",sf::Vector2f(app.getSize().x / 2 - 90, app.getSize().y / 2 - 200),32);
    Texts score("Your time: " + record,sf::Vector2f(app.getSize().x / 2 - 90, app.getSize().y / 2 - 100));

    Button buttonEnd(app, "Exit", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)+50));
    Button buttonTryAgain(app, "Try Again", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2) + 10));

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
        buttonEnd.update(app);
        buttonTryAgain.update(app);
        score.update(app);
        text.update(app);
        app.display();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (buttonEnd.isHover()) {
                app.close();
            }
            else if (buttonTryAgain.isHover())
            {
                return;
            }
        }
    }
}