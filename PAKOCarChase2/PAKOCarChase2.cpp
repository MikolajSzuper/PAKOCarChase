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

RenderWindow app(VideoMode(640, 480), "Pako Car Game",sf::Style::Close);
void GameOver(std::string record);
void NewGame();

int main()
{    
    app.setFramerateLimit(60);
    //app.setVerticalSyncEnabled(true);

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
    //Button buttonWhoBest(app, "Records", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)+50));
    Button buttonExit(app, "Exit", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2) + 50));

    Texts scoreboard_text("Scoreboard", sf::Vector2f(10,200),32);
    Texts scoreboard_text1("1. ...", sf::Vector2f(10, 230));
    Texts scoreboard_text2("2. ...", sf::Vector2f(10, 260));
    Texts scoreboard_text3("3. ...", sf::Vector2f(10, 290));

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
        //buttonWhoBest.update(app);
        buttonExit.update(app);
        if (scoreboard)
        {
            scoreboard_text.update(app);
            scoreboard_text1.update(app);
            scoreboard_text2.update(app);
            scoreboard_text3.update(app);
        }
        app.draw(logo);
        app.display();
        if (e.type == sf::Event::MouseButtonReleased)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (buttonPlay.isHover()) {
                    NewGame();
                }
                /*else if (buttonWhoBest.isHover())
                {
                    if (scoreboard)
                    {
                        scoreboard = 0;
                    }
                    else {
                        scoreboard = 1;
                    }
                }*/
                else if (buttonExit.isHover())
                {
                    return EXIT_SUCCESS;
                }
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
    Texts time("Time: ", sf::Vector2f(10.0f, 20.0f));
    sf::Clock clock;
    int s = 0, m = 0;
    int lose = 0;

    for (int i = 0; i < obs_how_many; i++)
    {
        obs[i].regenarateObstacle();
        while (obs[i].getObstacle().getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())) {
            obs[i].regenarateObstacle();
        }
    }

    sf::View gameView(sf::Vector2f(app.getSize().x/2, app.getSize().y/2), sf::Vector2f(app.getSize().x, app.getSize().y));

        while (app.isOpen())
        {
            Event e;
            while (app.pollEvent(e))
            {
                if (e.type == Event::Closed) {
                    app.close();
                }
            }

            if (e.type == Event::KeyReleased)
            {
                if (e.key.code == Keyboard::Right || e.key.code == Keyboard::Left || e.key.code == Keyboard::A || e.key.code == Keyboard::D)
                {
                   player. move();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) player.move("RIGHT");
            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) player.move("LEFT");

            Obstacle* wsk_obs = *&obs;

            // Timer and time draw update and bots Ai
            sf::Time elapsed = clock.getElapsedTime();
            //Bots Ai
            if(elapsed.asSeconds() >= 0.5f) {
                for (int i = 0; i < bots_how_many; i++)
                {
                    bots[i].onAi(player.getPos());
                }
            }
            if (elapsed.asSeconds() >= 1.f)
            {
                s++;
                clock.restart();
            }
            std::stringstream win_status;
            if (s > 59)
            {
                s = 0;
                m++;
            }
            win_status << std::setfill('0') << std::setw(2) << m << ":" << std::setw(2) << s;


            //Update player
            player.update(map.getMap(), wsk_obs, gameView);


            //Draw and display the main window of application
            app.clear(Color::White);

            app.draw(map.getMap());


            for (int i = 0; i < obs_how_many; i++)
            {
                app.draw(obs[i].getObstacle());
            }

            app.draw(player.getPlayer());
            //Draw bots and update them
            for (int i = 0; i < bots_how_many; i++)
            {
                if (player.Collison(bots[i])) {
                    lose = 1;
                }
                bots[i].update(map.getMap(), wsk_obs);
                app.draw(bots[i].getPlayer());
            }
            //app.draw(player.getSensor());
            app.setView(gameView);
            gameView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
            time.update(app, "Time: " + win_status.str(), gameView.getCenter() - sf::Vector2f((app.getSize().x/2) - 20, (app.getSize().y/2) - 20));
            app.display();

            //Game restart
            if (lose) {
                
                GameOver(win_status.str());
                player.restart();
                gameView.setCenter(app.getSize().x/2, app.getSize().y / 2);
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
                    while (obs[i].getObstacle().getGlobalBounds().intersects(player.getPlayer().getGlobalBounds())) {
                        obs[i].regenarateObstacle();
                    }
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

        app.setView(app.getDefaultView());
        app.clear(sf::Color(80, 80, 80));
        buttonEnd.update(app);
        buttonTryAgain.update(app);
        score.update(app);
        text.update(app);
        app.display();
        if (e.type == sf::Event::MouseButtonReleased)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
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
}