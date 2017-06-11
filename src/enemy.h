#include <SFML/Graphics.hpp>
#include "main.h"

//using namespace std;

#ifndef ENEMY
#define ENEMY

class Enemy : public Object {


    int enemyHP;
    float enemySpeed;
    int enemyStr;
    int enemyDef; 
    ActiveDirection playerMovement;
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    sf::Vector2i playerTexturePosition;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(playerSprite, states);
    }

public:

    Enemy();

};

#endif
