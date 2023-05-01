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

using namespace sf;

RenderWindow app(VideoMode(640, 480), "Pako Car Game");
void GameOver(std::string record);
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
    srand(time(NULL));
    const int obs_how_many = 10;
    const int bots_how_many = 3;
    Obstacle obs[obs_how_many];
    Ai bots[bots_how_many] = {
        Ai("assets/police.png", map.getBorder()),
        Ai("assets/police.png", map.getBorder()),
        Ai("assets/police.png", map.getBorder()),
    };
    int j = 0;
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
    }

    sf::Clock clock;
    int s=0, m=0;
    int lose = 0;
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
                NewGame();
            }
    }
}

void GameOver(std::string record) {

    sf::Font font;
    font.loadFromFile("assets/ROMAN SHINE.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(32);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getCharacterSize() / 2);
    text.setPosition(app.getSize().x / 2 - 90, app.getSize().y / 2 - 200);
    text.setString("Game Over");

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(24);
    score.setOrigin(score.getGlobalBounds().width / 2, score.getCharacterSize() / 2);
    score.setPosition(app.getSize().x / 2 - 90, app.getSize().y / 2 - 100);
    score.setString("Your time: "+ record);

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
        app.draw(score);
        app.draw(text);
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