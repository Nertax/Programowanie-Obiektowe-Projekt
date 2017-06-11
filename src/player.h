#include <SFML/Graphics.hpp>
#include "main.h"

using namespace std;

#ifndef PLAYER
#define PLAYER

class Player : public Object, public sf::Drawable {

    int playerHP;
    float playerSpeed;
    ActiveDirection playerMovement;
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    sf::Vector2u playerTexturePosition;
    sf::Clock moveAnimationClock;
    sf::Time lastMoveAnimationFrame;


    friend class Game;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(playerSprite, states);
    }


public:

    Player();

    void activeMovementDirection(int direction);
    void deactiveMovementDirection(int direction);

    void setPlayerPosition(float newXPosition, float newYPosition);

    float getPlayerSpeed() { return this->playerSpeed; }


    Position getFuturePlayerPosition(int moveDirection, sf::Time timeBetweenFrames);

    void movePlayer(int moveDirection, sf::Time timeBetweenFrames);
};
#endif
