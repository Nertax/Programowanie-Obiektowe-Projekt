#include "game.h"

Game::Game() {


    window.create(sf::VideoMode(200, 200), "Decouyon Game");
    window.setFramerateLimit(59);
    window.setView(myView);

    myView.setCenter(player.getObjectPosition().x +16, player.getObjectPosition().y +16);
    myView.setSize(200, 200);

    mojaMapa.loadMap("mapDecuyon", "mapDecuyon.png", sf::Vector2u(32, 32));
    mojePrzeszkody.loadObstacles("obstaclesDecuyon", "obstaclesDecuyon.png", sf::Vector2u(32, 32));
}



void Game::update(sf::Time timeBetweenFrames) {

        //jesli gracz sie nie porusza to animacje ruchu ustawiamy na pozycje "stoi"
        if(player.playerMovement.down == 0 &&
           player.playerMovement.left == 0 &&
           player.playerMovement.right == 0 &&
           player.playerMovement.up == 0)
           {
            player.playerTexturePosition.x = 1;
            player.playerSprite.setTextureRect(sf::IntRect(player.playerTexturePosition.x * 32, player.playerTexturePosition.y * 32, 32, 32));
           }
        //jesli nie to aktualizujemy ruch gracza
        else {
            if(player.playerMovement.down == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(0, timeBetweenFrames);
                Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

                if(temp == NULL) {
                    player.movePlayer(0, timeBetweenFrames);
                }
            }

            if(player.playerMovement.left == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(1, timeBetweenFrames);
                Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

                if(temp == NULL) {
                    player.movePlayer(1, timeBetweenFrames);
                }
            }

            if(player.playerMovement.right == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(2, timeBetweenFrames);
                Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

                if(temp == NULL) {
                    player.movePlayer(2, timeBetweenFrames);
                }
            }

            if(player.playerMovement.up == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(3, timeBetweenFrames);
                Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

                if(temp == NULL) {
                    player.movePlayer(3, timeBetweenFrames);
                }
            }
        }

        //aktualizujemy kamere
        myView.setCenter(player.getObjectPosition().x +16, player.getObjectPosition().y +16);
}

void Game::runGame() {


    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) {
                    player.activeMovementDirection(Up);
                }
                if (event.key.code == sf::Keyboard::A) {
                    player.activeMovementDirection(Left);
                }
                if (event.key.code == sf::Keyboard::S) {
                    player.activeMovementDirection(Down);
                }
                if (event.key.code == sf::Keyboard::D) {
                    player.activeMovementDirection(Right);
                }
            }

            if(event.type == sf::Event::KeyReleased) {

                if (event.key.code == sf::Keyboard::W) {
                    player.deactiveMovementDirection(Up);
                }

                if (event.key.code == sf::Keyboard::A) {
                    player.deactiveMovementDirection(Left);
                }

                if (event.key.code == sf::Keyboard::S) {
                    player.deactiveMovementDirection(Down);
                }

                if (event.key.code == sf::Keyboard::D) {
                    player.deactiveMovementDirection(Right);
                }
            }
        }

        window.clear();
        
        update(frameClock.restart());

        window.setView(myView);
        window.draw(mojaMapa);
        window.draw(mojePrzeszkody);
        window.draw(player);


        window.display();
    }
}

