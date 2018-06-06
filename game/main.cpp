#include "game.h"
#include "player.hpp"
#include "map.hpp"
#include "flower.hpp"

int main()
{
    sf::Clock           clock;
    
    sf::RenderWindow    window (sf::VideoMode(2120, 920), "test");
    
    //sf::View            view;
    //view.reset(sf::FloatRect(0, 0, 1280, 640));
    
    sf::Texture         player_texture;
    player_texture.loadFromFile ("image/devil.png");
    
    sf::Texture         map_texture;
    map_texture.loadFromFile ("image/test_map.png");
    
    objmanager objs;
    
    sf::String scheme [30] {
        "00000000000000000000000000000000000000000000000000000000000000000",
        "0                                                               0",
        "0                  h                                            0",
        "0                                                          s    0",
        "0                                                               0",
        "0      ss                                                       0",
        "0      ss                                                       0",
        "0                                                               0",
        "0                                                               0",
        "0                                                               0",
        "0                                                               0",
        "0                                                               0",
        "0                                                               0",
        "0                                                               0",
        "0                         h                                     0",
        "0          s                                                s   0",
        "0                                                               0",
        "0                                                               0",
        "0                                                               0",
        "0                                                               0",
        "0                                          h                    0",
        "0  s                   s                                        0",
        "0                                                               0",
        "0                                                               0",
        "00000000000000000000000000000000000000000000000000000000000000000"
    };
    
    objs.create (new map (65, 30, 32, map_texture, scheme));
    
    objs.create (new player (player_texture, 150, 150));
    
    objs.create (new flower (map_texture, 400, 400));
    
    objs.create (new flower (map_texture, 700, 700));
    
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
        
        window.display();
    }
    
    return 0;
}
