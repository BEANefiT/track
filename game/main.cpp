#include <iostream>
#include "game.h"
#include "player.hpp"
#include "map.hpp"
#include "flower.hpp"
#include "heart.hpp"
#include "finish.hpp"

int main()
{
    sf::Clock           clock;
    
    sf::RenderWindow    window (sf::VideoMode(1312, 1312), "test");
    
    sf::Font            font;
    font.loadFromFile   ("font/lunchds.ttf");
    
    sf::Text            text ("", font, 100);
    
    //sf::View            view;
    //view.reset(sf::FloatRect(0, 0, 1280, 640));
    
    sf::Texture         player_texture;
    player_texture.loadFromFile ("image/devil.png");
    
    sf::Texture         map_texture;
    map_texture.loadFromFile ("image/map.png");
    
    objmanager objs;
    
    sf::String scheme [41] {
        "00000000000000000000000000000000000000000",
        "0   s   s   s   s       s   s s         0",
        "0ss s sss sss sss s sss s s s s sssss ss0",
        "0   s   s s   s   s s s s s   s s   s   0",
        "0 sssss s s sss sss s s s sssss s s sss 0",
        "0     s s s     s s s s s     s   s s   0",
        "0ssss s s sssssss s s s sssss sss s s ss0",
        "0                   s s           s s   0",
        "0 sssssssssssssssssss sssssssssssss sss 0",
        "0 s   s       s         s             s 0",
        "0 s sss sssssss sss sss s sssssss s sss 0",
        "0               s   s   s       s s s   0",
        "0ssssss sss sssss sssss sss sss s s s ss0",
        "0   s   s s   s   s   s   s s s s s s s 0",
        "0 s s s s sssss sss s s s s s s sss s s 0",
        "0 s s s s s     s   s s s s   s s   s   0",
        "0 sss sss s sssss sss s sssssss s sssss 0",
        "0     s   s     s   s s       s s s     0",
        "0ssssss sssssssssss s sssss s s sss ssss0",
        "0             s     s s     s s s   s    ",
        "0 s sssssss s s sssss s sss s s s sssss 0",
        "0 s       s s s s     s   s s s s     s 0",
        "0 sssssss s s s sss sssssss s s sssss s 0",
        "0   s     s s s   s         s s s   s s 0",
        "0ssss sssss s sss s sssssssssss s s s s 0",
        "0     s   s s s   s s           s s   s 0",
        "0 sssss s sss sssss s s s sssssssssssss 0",
        "0   s   s           s s s         s   s 0",
        "0ssss sssssssssss sss s s sssssss s sss 0",
        "0     s     s     s s s s       s       0",
        "0 s sss sssss sssss s s sssssss sss sss 0",
        "0 s s   s     s   s   s s     s s   s   0",
        "0 s sss s sssss s sssss s sssss ssssssss0",
        "0 s s   s       s s     s s   s     s   0",
        "0ss s sssssssssss s sss s s s sssss s s 0",
        "0   s       s     s   s s   s     s   s 0",
        "0 sssss s sss sssssssss sssssssss s sss 0",
        "0 s     s     s       s             s   0",
        "0 s sssssssssss sssss sssssssssssss s ss0",
        "0 s             s     s             s   0",
        "00000000000000000000000000000000000000000"
    };
    
    gameobj* you = new player (player_texture, 0, 576);
    
    gameobj* end = new finish (map_texture, 1280, 608);
    
    objs.create (new map (41, 41, 32, map_texture, scheme));
    
    objs.create (you);
    
    objs.create (end);
    
    //objs.create (new flower (map_texture, 32, 600, 100));
    
    //objs.create (new flower (map_texture, 700, 700, 50));
    
    //objs.create (new heart  (map_texture, 300, 200, 20));
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //struct vector player_coord = objs [1] -> getPosition();
        //view.setCenter (player_coord.x, player_coord.y);
        //window.setView (view);
        window.clear(sf::Color(58, 58, 58));
        
        objs.run (window, clock.getElapsedTime().asMicroseconds() / 1000);
        
        clock.restart();
    
        if (!(you -> isAlive()))
        {
            text.setString ("Unlucky ;(");
            text.setPosition (410, 350);
        }
        
        if (!(end -> isAlive()))
        {
            text.setString ("Victory :)");
            text.setPosition (410, 350);
        }
        
        window.draw (text);
        
        window.display();
    }
    
    return 0;
}
