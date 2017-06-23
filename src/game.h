#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"
#include "obstacle.h"
#include "enemy.h"
#include <sstream>

#ifndef GAME
#define GAME

class Game {

    sf::Clock frameClock;
    sf::Clock mainClock;

    Player player;
    enum playerMove { Down, Left, Right, Up };

    sf::RenderWindow window;
    sf::View myView;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape UiBackground;
    sf::RectangleShape playerHPLine;
    Map mojaMapa;
    Obstacles mojePrzeszkody;
    Monsters potwory;

public:

    //ustawiamy wartosci poczatkowe, wczytujemy tekstury, font itd
    Game();

    //glowna funkcja aktualuzujaca gre
    void update(sf::Time timeBetweenFrames);

    //funkcja rysuje UI
    void drawUI();

    //glowna petla gry
    void runGame();
};
#endif

