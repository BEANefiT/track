#include <SFML/Graphics.hpp>

enum direction
{
    left_down   = 0,
    down        = 1,
    right_down  = 2,
    left        = 3,
    left_up     = 4,
    right       = 5,
    right_up    = 6,
    up          = 7
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
        float           default_speed;
        float           diag_speed;
        enum direction  _dir;
       
    public:      
        sf::Sprite      sprite;

        void    upd (sf::RenderWindow&, float time);
        void    speed (enum direction);

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
            default_speed   (0.4),
            diag_speed      (0.4 / 1.41),
            _dir            (down)

            {};

        virtual void check (enum sf::Keyboard::Key, enum sf::Keyboard::Key, enum sf::Keyboard::Key, enum sf::Keyboard::Key) = 0;
};

class player: public gameobj
{
    public:
        player (sf::Texture* t, float x, float y):
            gameobj (t, 96, 96, x, y, 0, 0, 0, 0)
        {
            sprite.setTexture (*t);
            sprite.setPosition (_x, _y);
        };

        void move(float time) override
        {
            if (_vx == 0 && _vy == 0)
            {
                sprite.setTextureRect (sf::IntRect (0, _dir * 100, 100, 100));
                sprite.setScale (sf::Vector2f (2.f, 2.f));
                return;
            }

            if (_vx > 0)
            {
                if (_vy > 0)
                {
                    _dir = right_down;
                    _vx  = diag_speed;
                    _vy  = diag_speed;
                }

                if (_vy < 0)
                {
                    _dir = right_up;
                    _vx  = diag_speed;
                    _vy  = -diag_speed;
                }
            }

            if (_vx < 0)
            {
                if (_vy > 0)
                {
                    _dir = left_down;
                    _vx  = -diag_speed;
                    _vy  = diag_speed;
                }

                if (_vy < 0)
                {
                    _dir = left_up;
                    _vx  = -diag_speed;
                    _vy  = -diag_speed;
                }
            }

            sprite.move (_vx * time, _vy * time);
            sprite.setTextureRect (sf::IntRect (100 * (int)_frame_num, _dir * 100, 100, 100));
            _vx = 0;
            _vy = 0;

            _frame_num += 0.0105;

            if (_frame_num > 9)
                _frame_num = 1;
        }

        virtual void check (enum sf::Keyboard::Key w, enum sf::Keyboard::Key a, enum sf::Keyboard::Key s, enum sf::Keyboard::Key d) override
        {
            if (sf::Keyboard::isKeyPressed (w)) { speed (up)   ; }
            if (sf::Keyboard::isKeyPressed (a)) { speed (left) ; }
            if (sf::Keyboard::isKeyPressed (s)) { speed (down) ; }
            if (sf::Keyboard::isKeyPressed (d)) { speed (right); }
        }
};

void gameobj::upd(sf::RenderWindow& window, float time)
{
    move (time);
    window.draw (sprite);
}

void gameobj::speed (enum direction dir)
{
    _dir = dir;

    switch (dir)
    {
        case down:  { _vy = default_speed       ; break; }

        case left:  { _vx = default_speed * (-1); break; }

        case right: { _vx = default_speed       ; break; }

        case up:    { _vy = default_speed * (-1); break; }
    }
}

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1440, 720), "test");

    sf::Image img;
    img.loadFromFile ("image/girl.png");

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

        float time = clock.getElapsedTime().asMicroseconds() / 800;

        for (int i = 0; i < 15; i++)
            if (objs [i])
                objs [i] -> upd (window, time);

        clock.restart();

        window.display();
    }

    return 0;
}
