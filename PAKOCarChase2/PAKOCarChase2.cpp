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
#include <Windows.h>

using namespace sf;

RenderWindow app(VideoMode(1920, 1080), "Pako Car Game", sf::Style::Close);
void GameOver(std::string record);
void NewGame();

int main()
{    

    app.setFramerateLimit(60);
    //app.setVerticalSyncEnabled(true);

    sf::Sprite logo;
    sf::Texture tex_logo;
    tex_logo.loadFromFile("assets/logo.png");
    logo.setTexture(tex_logo);
    logo.setOrigin(193,96.5);
    logo.setPosition(sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)-225));
    logo.scale(1,1);

    sf::Image icon;
    icon.loadFromFile("assets/icon.png");
    app.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Button buttonPlay(app, "Play", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)));
    Button buttonExit(app, "Exit", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2) + 75));

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
        buttonPlay.update(app, sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)));
        buttonExit.update(app, sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2) + 75));
        app.draw(logo);
        app.display();
        if (e.type == sf::Event::MouseButtonReleased)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (buttonPlay.isHover()) {
                    NewGame();
                }
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
    HWND handle = app.getSystemHandle(); 
    ShowWindow(handle, SW_MAXIMIZE);
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
    sf::Vector2f time_pos = {20,20};
    Texts time("Time: ", {20,20});
    sf::Clock clock;
    int s = 0, m = 0;
    int lose = 0;
    bool Left_click = 0, Right_click = 0;


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
                if (e.key.code == Keyboard::Right || e.key.code == Keyboard::D)
                {
                   Right_click = 0;
                }
                else if (e.key.code == Keyboard::Left || e.key.code == Keyboard::A) 
                {
                    Left_click = 0;
                }
                player.move();
            }
            if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
                if (!Left_click)
                {
                    Right_click = 1;
                    player.move("RIGHT");
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)){
                if (!Right_click) {
                    Left_click = 1;
                    player.move("LEFT");
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                app.close();
            }

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
            time_pos = time_pos - player.update(map.getMap(), wsk_obs, gameView);


            //Draw and display the main window of application
            app.clear(sf::Color(30,44.7,10.6));

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

            time.update(app, "Time: " + win_status.str(), time_pos);
            app.display();

            //Game restart
            if (lose) {
                
                GameOver(win_status.str());
                ShowWindow(handle, SW_MAXIMIZE);
                time_pos = { 20,20 };
                player.restart();
                gameView.setCenter(app.getSize().x/2, app.getSize().y / 2);
                lose = 0;
                m = 0;
                s = 0;
                Right_click = 0;
                Left_click = 0;
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
    HWND handle = app.getSystemHandle(); 
    ShowWindow(handle, SW_NORMAL);
    app.clear();
    Texts text("Game Over",sf::Vector2f(app.getSize().x / 2 - 120, app.getSize().y / 2 - 400),48);
    Texts score("Your time: " + record,sf::Vector2f(app.getSize().x / 2 - 120, app.getSize().y / 2 - 200));

    Button buttonEnd(app, "Exit", sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2)+85));
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
        buttonEnd.update(app, sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2) + 85));
        buttonTryAgain.update(app, sf::Vector2f(app.getSize().x / 2, (app.getSize().y / 2) + 10));
        score.update(app, sf::Vector2f(app.getSize().x / 2 - 120, app.getSize().y / 2 - 200));
        text.update(app, sf::Vector2f(app.getSize().x / 2 - 120, app.getSize().y / 2 - 400));
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