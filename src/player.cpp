#include "player.h"

Player::Player() { 
    this->playerHP = 100;
    this->deactiveMovementDirection(0);
    this->deactiveMovementDirection(1);
    this->deactiveMovementDirection(2);
    this->deactiveMovementDirection(3);
    this->setObjectPosition(50 ,10);
    this->playerSprite.setPosition( getObjectPosition().x, getObjectPosition().y );
    this->playerSpeed = 100;
    this->playerAttackRange = 10;
    this->playerStr = 7;
    this->playerTexturePosition.x = 1;
    this->playerTexturePosition.y = 0;
    this->attackFlag = 0;
    this->lastAttackTime = sf::seconds(0);
    this->attackCooldown = sf::seconds(0.4);
    playerTexture.loadFromFile("data/textures/player.png");
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));
    }

    void Player::activeMovementDirection(int direction) {

        if(direction == 0)
            this->playerMovement.down = 1;

        if(direction == 1)
            this->playerMovement.left = 1;

        if(direction == 2)
            this->playerMovement.right = 1;

        if(direction == 3)
            this->playerMovement.up = 1;
    }

    void Player::deactiveMovementDirection(int direction) {

        if(direction == 0)
            this->playerMovement.down = 0;

        if(direction == 1)
            this->playerMovement.left = 0;

        if(direction == 2)
            this->playerMovement.right = 0;

        if(direction == 3)
            this->playerMovement.up = 0;
    }

    void Player::setPlayerPosition(float newXPosition, float newYPosition) {

        this->setObjectPosition(newXPosition, newYPosition);
        this->playerSprite.setPosition(newXPosition, newYPosition);

    }

    Position Player::getFuturePlayerPosition(int moveDirection, sf::Time timeBetweenFrames) {

        Position temp = this->getObjectPosition();

        if(moveDirection == 0) 
            temp.y += playerSpeed * timeBetweenFrames.asSeconds();

        else if(moveDirection == 1)
            temp.x -= playerSpeed * timeBetweenFrames.asSeconds();

        else if(moveDirection == 2) 
            temp.x +=playerSpeed * timeBetweenFrames.asSeconds();

        else if(moveDirection == 3) 
            temp.y -= playerSpeed * timeBetweenFrames.asSeconds();  

        return temp;
    }

    void Player::movePlayer(int moveDirection, sf::Time timeBetweenFrames) {

        if(moveDirection == 0) {
            this->playerTexturePosition.y = 0;

            if(this->moveAnimationClock.getElapsedTime() - this->lastMoveAnimationFrame > sf::milliseconds(4000) / this->getPlayerSpeed()) {

                if(this->playerTexturePosition.x == 0)
                    this->playerTexturePosition.x = 2;
                else
                    this->playerTexturePosition.x = 0;

                this->lastMoveAnimationFrame = moveAnimationClock.getElapsedTime();
            }

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));

            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x, currentPosition.y += playerSpeed * timeBetweenFrames.asSeconds());
        }

        if(moveDirection == 1) {
            this->playerTexturePosition.y = 1;

            if(this->moveAnimationClock.getElapsedTime() - this->lastMoveAnimationFrame > sf::milliseconds(4000) / this->getPlayerSpeed()) {

                if(this->playerTexturePosition.x == 0)
                    this->playerTexturePosition.x = 2;
                else
                    this->playerTexturePosition.x = 0;

                this->lastMoveAnimationFrame = moveAnimationClock.getElapsedTime();
            }

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));


            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x -= playerSpeed * timeBetweenFrames.asSeconds(), currentPosition.y );
        }

        if(moveDirection == 2) {
            this->playerTexturePosition.y = 2;

            if(this->moveAnimationClock.getElapsedTime() - this->lastMoveAnimationFrame > sf::milliseconds(4000) / this->getPlayerSpeed()) {

                if(this->playerTexturePosition.x == 0)
                    this->playerTexturePosition.x = 2;
                else
                    this->playerTexturePosition.x = 0;

                this->lastMoveAnimationFrame = moveAnimationClock.getElapsedTime();
            }

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));


            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x += playerSpeed * timeBetweenFrames.asSeconds(), currentPosition.y );
        }

        if(moveDirection == 3) {
            this->playerTexturePosition.y = 3;

            if(this->moveAnimationClock.getElapsedTime() - this->lastMoveAnimationFrame > sf::milliseconds(4000) / this->getPlayerSpeed()) {

                if(this->playerTexturePosition.x == 0)
                    this->playerTexturePosition.x = 2;
                else
                    this->playerTexturePosition.x = 0;

                this->lastMoveAnimationFrame = moveAnimationClock.getElapsedTime();
            }

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));


            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x, currentPosition.y -= playerSpeed * timeBetweenFrames.asSeconds());
        }
    }


