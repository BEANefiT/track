#include "gameobj.hpp"
#include "player.hpp"
#include "map.hpp"

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1440, 720), "test");

    sf::Texture player_texture;
    player_texture.loadFromFile ("image/devil.png");

    sf::Texture map_texture;
    map_texture.loadFromFile ("image/test_map.png");

    gameobj *objs [15] = {};
    objs[0] = new map ( 20, 15, 3, 32, &map_texture, 3, " s0",
                        {
                            "00000000000000000000"
                            "0                  0"
                            "0                  0"
                            "0             s    0"
                            "0                  0"
                            "0                  0"
                            "0      s           0"
                            "0                  0"
                            "0                  0"
                            "0                  0"
                            "0          s       0"
                            "0                  0"
                            "0                  0"
                            "0                  0"
                            "00000000000000000000"
                                                });

    objs[1] = new player (&player_texture, 150, 150);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        objs [1] -> check (sf::Keyboard::W, sf::Keyboard::A, sf::Keyboard::S, sf::Keyboard::D);

        window.clear(sf::Color(58, 58, 58));

        float time = clock.getElapsedTime().asMicroseconds() / 400;

        for (int i = 0; i < 15; i++)
            if (objs [i])
                objs [i] -> upd (&window, time);

        clock.restart();

        window.display();
    }

    return 0;
}
