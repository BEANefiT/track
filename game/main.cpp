#include <SFML/Graphics.hpp>

#define iskey sf::Keyboard::isKeyPressed

enum direction
{
    left_down   = 5,
    down        = 4,
    right_down  = 3,
    left        = 6,
    left_up     = 7,
    right       = 2,
    right_up    = 1,
    up          = 0
};
 
class gameobj
{
    protected:
        sf::Texture*    _texture;
        float           _frame_num;
        float           _width;
        float           _height;
        float           _x;
        float           _y;
        float           _vx;
        float           _vy;
        float           _ax;
        float           _ay;
        enum direction  _dir;
       
    public:      
        sf::Sprite      sprite;

        void    upd (sf::RenderWindow&, float time);
        void    speed (enum direction, float v);

        virtual void move (float time) = 0;

        gameobj (   sf::Texture* texture, float width, float height, float x, float y,
                    float vx, float vy, float ax, float ay):
            _texture        (texture),
            _frame_num      (0),
            _width          (width),
            _height         (height),
            _x              (x),
            _y              (y),
            _vx             (vx),
            _vy             (vy),
            _ax             (ax),
            _ay             (ay),
            _dir            (down)

            {};

        virtual void check (enum sf::Keyboard::Key, enum sf::Keyboard::Key, enum sf::Keyboard::Key, enum sf::Keyboard::Key) = 0;
};

class player: public gameobj
{
    protected:
        float default_speed;
        float diag_speed;

    public:
        player (sf::Texture* t, float x, float y):
            gameobj (t, 96, 96, x, y, 0, 0, 0, 0),
            default_speed (0.1)
        {
            diag_speed = default_speed / 1.41;
            sprite.setTexture (*t);
            sprite.setPosition (_x, _y);
        };

        void move(float time) override
        {
            if (_vx == 0 && _vy == 0)
            {
                sprite.setTextureRect (sf::IntRect (2 * 96, _dir * 96, 96, 96));
                return;
            }

            sprite.move (_vx * time, _vy * time);
            sprite.setTextureRect (sf::IntRect (96 * (int)_frame_num, _dir * 96, 96, 96));
            _vx = 0;
            _vy = 0;

            _frame_num += 0.01;

            if (_frame_num > 8)
                _frame_num = 1;
        }

        virtual void check (enum sf::Keyboard::Key w, enum sf::Keyboard::Key a, enum sf::Keyboard::Key s, enum sf::Keyboard::Key d) override
        {
            if (iskey (a))
            {
                if (iskey (w))  { speed (left_up, diag_speed); return; }
                    
                if (iskey (s))  { speed (left_down, diag_speed); return; }

                speed (left, default_speed);

                return;
            }

            if (iskey (d))
            {
                if (iskey (w))  { speed (right_up, diag_speed); return; }
                    
                if (iskey (s))  { speed (right_down, diag_speed); return; }

                speed (right, default_speed);

                return;
            }

            if (iskey (w))
            {
                speed (up, default_speed);

                return;
            }

            if (iskey (s))
            {
                speed (down, default_speed);

                return;
            }
        }
};

void gameobj::upd(sf::RenderWindow& window, float time)
{
    move (time);
    window.draw (sprite);
}

void gameobj::speed (enum direction dir, float v)
{
    _dir = dir;

    switch (dir)
    {
        case down:       { _vy =  v;           break; }

        case left:       { _vx = -v;           break; }

        case right:      { _vx =  v;           break; }

        case up:         { _vy = -v;           break; }

        case right_up:   { _vy = -v; _vx =  v; break; }
    
        case right_down: { _vy =  v; _vx =  v; break; }

        case left_up:    { _vy = -v; _vx = -v; break; }

        case left_down:  { _vy =  v; _vx = -v; break; }
    }
}

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
