#include "gameobj.hpp"
#include "player.hpp"

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1440, 720), "test");

    sf::Image img;
    img.loadFromFile ("image/devil.png");

    sf::Texture texture;
    texture.loadFromImage (img);

    gameobj *objs [15] = {};
    objs[0] = new player (&texture, 150, 150);
    objs[1] = new player (&texture, 150, 300);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        objs [0] -> check (sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Down, sf::Keyboard::Right);
        objs [1] -> check (sf::Keyboard::W,  sf::Keyboard::A,    sf::Keyboard::S,    sf::Keyboard::D);

        window.clear(sf::Color(58, 58, 58));

        float time = clock.getElapsedTime().asMicroseconds() / 500;

        for (int i = 0; i < 15; i++)
            if (objs [i])
                objs [i] -> upd (window, time);

        clock.restart();

        window.display();
    }

    return 0;
}
