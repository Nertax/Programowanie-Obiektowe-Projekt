#include "game.h"

Game::Game() {


    window.create(sf::VideoMode(200, 200), "Decouyon Game");
    window.setFramerateLimit(59);
    window.setView(myView);

    myView.setCenter(player.getObjectPosition().x +16, player.getObjectPosition().y +16);
    myView.setSize(200, 200);

    mojaMapa.loadMap("mapDecuyon", "mapDecuyon.png", sf::Vector2u(32, 32));
    mojePrzeszkody.loadObstacles("obstaclesDecuyon", "obstaclesDecuyon.png", sf::Vector2u(32, 32));

    potwory.loadOgrs("ogrsPositions", "ogr.png");
}



void Game::update(sf::Time timeBetweenFrames) {

    //sprawdzam czy gracza atakuje i czy cooldown ataku mu na to pozwala
    if(player.attackFlag == 1 && (this->mainClock.getElapsedTime() - player.lastAttackTime) > player.attackCooldown) {


        Enemy* enemyInRange = potwory.getMonsterOnAtackArea(player.objectPosition, player.playerTexturePosition.y, player.playerAttackRange);
        if(enemyInRange != NULL) {


            enemyInRange->setEnemyHP(enemyInRange->getEnemyHP() - (player.playerStr - enemyInRange->getEnemyDef()));
        }

        player.lastAttackTime = mainClock.getElapsedTime();
        


    }

    //jesli gracz nie atakuje i sie nie porusza to animacje ruchu ustawiamy na pozycje "stoi"
    else if(player.playerMovement.down == 0 &&
           player.playerMovement.left == 0 &&
           player.playerMovement.right == 0 &&
           player.playerMovement.up == 0)
           {
            player.playerTexturePosition.x = 1;
            player.playerSprite.setTextureRect(sf::IntRect(player.playerTexturePosition.x * 32, player.playerTexturePosition.y * 32, 32, 32));
           }
        //jesli nie atakuje i nie stoi, to aktualizujemy ruch gracza
        else {
            if(player.playerMovement.down == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(0, timeBetweenFrames);
                Obstacle* tempObstacle = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);
                Enemy* tempEnemy = potwory.getMonsterOnPosition(futurePlayerPosition);

                if(tempObstacle == NULL && tempEnemy == NULL) {
                    player.movePlayer(0, timeBetweenFrames);
                }
            }

            if(player.playerMovement.left == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(1, timeBetweenFrames);
                Obstacle* tempObstacle = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);
                Enemy* tempEnemy = potwory.getMonsterOnPosition(futurePlayerPosition);

                if(tempObstacle == NULL && tempEnemy == NULL) {
                    player.movePlayer(1, timeBetweenFrames);
                }
            }

            if(player.playerMovement.right == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(2, timeBetweenFrames);
                Obstacle* tempObstacle = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);
                Enemy* tempEnemy = potwory.getMonsterOnPosition(futurePlayerPosition);

                if(tempObstacle == NULL && tempEnemy == NULL) {
                    player.movePlayer(2, timeBetweenFrames);
                }
            }

            if(player.playerMovement.up == 1) {
                Position futurePlayerPosition = player.getFuturePlayerPosition(3, timeBetweenFrames);
                Obstacle* tempObstacle = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);
                Enemy* tempEnemy = potwory.getMonsterOnPosition(futurePlayerPosition);

                if(tempObstacle == NULL && tempEnemy == NULL) {
                    player.movePlayer(3, timeBetweenFrames);
                }
            }
        }

        //aktualizujemy kamere
        myView.setCenter(player.getObjectPosition().x +16, player.getObjectPosition().y +16);

        //aktualizuje potowry - usmierca je i respawnuje
        potwory.updateDeadMonsters(mainClock.getElapsedTime());

}

void Game::runGame() {


    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                //sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                //window.setView(sf::View(visibleArea));
                myView.setSize(event.size.width, event.size.height);
            }

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
                if (event.key.code == sf::Keyboard::Space) {
                    player.attackFlag = 1;
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

                if (event.key.code == sf::Keyboard::Space) {
                    player.attackFlag = 0;
                }
            }
        }

        window.clear();
        
        update(frameClock.restart());

        window.setView(myView);
        window.draw(mojaMapa);
        window.draw(mojePrzeszkody);
        potwory.drawOgrs(window);
        window.draw(player);


        window.display();
    }
}

