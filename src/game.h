#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include "obstacle.h"

#ifndef GAME
#define GAME

class Game {

    sf::Clock frameClock;
    Player player;
    enum playerMove { Down, Left, Right, Up };

    sf::RenderWindow window;
    sf::View myView;
    Map mojaMapa;
    Obstacles mojePrzeszkody;


public:

    Game();

    void update(sf::Time timeBetweenFrames);

    void runGame();
};
#endif

