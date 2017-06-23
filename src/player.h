#include <SFML/Graphics.hpp>
#include "main.h"

using namespace std;

#ifndef PLAYER
#define PLAYER

class Player : public Object, public sf::Drawable {

    int playerHP;
    int playerMaxHP;
    float playerSpeed;
    float playerAttackRange;
    int playerStr;
    int exp;
    int lvl;
    ActiveDirection playerMovement;
    bool attackFlag;
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    sf::Vector2u playerTexturePosition;
    sf::Clock moveAnimationClock;
    sf::Time lastMoveAnimationFrame;
    sf::Time lastAttackTime;
    sf::Time attackCooldown;


    //tak latwiej, chociaz czesc klasy player robiona byla bez tego dlatego widac mometami pewne rozbieznosci w stylu kodu
    friend class Game;

    //potrzebne by moc rysowac z gracza w glownej petli
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(playerSprite, states);
    }


public:

    Player();

    //funkcje aktywujace i dezaktywujace poruszanie sie w danym kierunku
    void activeMovementDirection(int direction);
    void deactiveMovementDirection(int direction);

    //ustaw pozycje gracza (wraz z pozzycja jego tekstury) na zadana pozycje
    void setPlayerPosition(float newXPosition, float newYPosition);
    
    //funkca zwraca gdzie gracza bedzie jesli sie poruszy w zadanym kierunku
    Position getFuturePlayerPosition(int moveDirection, sf::Time timeBetweenFrames);

    //glowna funkcja poruszania gracza
    void movePlayer(int moveDirection, sf::Time timeBetweenFrames);


    //podstawowe funkcje
    float getPlayerSpeed() { return this->playerSpeed; }
    int getPlayerLvl() { return this->lvl; }
    void setPlayerLvl(int value) { this->lvl = value; }
    int getPlayerExp() { return this->exp; }
    void setPlayerExp(int value) { this->exp = value; }

};
#endif
