#include "game.h"

//ustawiamy wartosci poczatkowe, wczytujemy tekstury, font itd
Game::Game() {
    window.create(sf::VideoMode(200, 200), "Decouyon Game");
    window.setFramerateLimit(59);
    window.setView(myView);
    font.loadFromFile("data/data-latin.ttf");

    text.setFont(font); 
    text.setCharacterSize(18);


    UiBackground.setFillColor(sf::Color(20, 20, 20));
    playerHPLine.setFillColor(sf::Color(255, 0, 0));


    myView.setCenter(player.getObjectPosition().x +16, player.getObjectPosition().y +16);
    myView.setSize(200, 200);

    mojaMapa.loadMap("mapDecuyon", "mapDecuyon.png", sf::Vector2u(32, 32));
    mojePrzeszkody.loadObstacles("obstaclesDecuyon", "obstaclesDecuyon.png", sf::Vector2u(32, 32));

    potwory.loadOgrs("ogrsPositions", "ogr.png");
}



//glowna funkcja aktualuzujaca gre
void Game::update(sf::Time timeBetweenFrames) {

    //sprawdzam czy gracz atakuje i czy cooldown ataku mu na to pozwala
    if(player.attackFlag == 1 && (this->mainClock.getElapsedTime() - player.lastAttackTime) > player.attackCooldown) {

        //szukamy czy jakis potwor w zasiegu ataku
        Enemy* enemyInRange = potwory.getMonsterOnAtackArea(player.objectPosition, player.playerTexturePosition.y, player.playerAttackRange);
        if(enemyInRange != NULL) {

            //jesli tak to zaatakuj go
            enemyInRange->setEnemyHP(enemyInRange->getEnemyHP() - (player.playerStr + player.lvl - enemyInRange->getEnemyDef()));
        }

        //ustaw cooldown ataku gracza
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
        potwory.updateDeadMonsters(mainClock.getElapsedTime(), player);
}


//funkcja rysuje UI
void Game::drawUI() {

    //ustawia tlo UI
    UiBackground.setSize(sf::Vector2f(200, 70));
    UiBackground.setPosition(sf::Vector2f(myView.getCenter().x - myView.getSize().x/2, myView.getCenter().y - myView.getSize().y/2));

    //ustawia pasek HP gracza
    playerHPLine.setPosition(sf::Vector2f(myView.getCenter().x - myView.getSize().x/2, myView.getCenter().y - myView.getSize().y/2));
    playerHPLine.setSize(sf::Vector2f(200 * player.playerHP / player.playerMaxHP, 20));
    
    //ustawia wyswietlanie expa gracza
    ostringstream tempExp, tempLvl, tempExpLvlUp;
    tempExp << player.getPlayerExp();
    tempExpLvlUp << player.getPlayerLvl() * 100;
    string expSring = tempExp.str();
    string lvlString = tempExpLvlUp.str();
    text.setPosition(sf::Vector2f(UiBackground.getPosition().x + 3, UiBackground.getPosition().y + 23));
    text.setString("Exp: " + expSring + "/" + lvlString);

    //wyswietla wyzej ustawione elementy
    window.draw(UiBackground);
    window.draw(playerHPLine);
    window.draw(text);

    //ustawia wyswietlanie lvlu gracza i go wyswietla
    tempLvl << player.getPlayerLvl();
    lvlString = tempLvl.str();
    text.setPosition(sf::Vector2f(UiBackground.getPosition().x + 3, UiBackground.getPosition().y + 44));
    text.setString("Lvl: " + lvlString);
    window.draw(text);
}



//glowna petla gry
void Game::runGame() {

    while(window.isOpen())
    {
        //wylapywanie eventow
        sf::Event event;
        while (window.pollEvent(event))
        {

            //co ma sie dziac podczas resize okna
            if (event.type == sf::Event::Resized)
                myView.setSize(event.size.width, event.size.height);

            //co ma sie dziac po nacisnieciu x na pasku
            if (event.type == sf::Event::Closed)
                window.close();

            //wylapywanie nacisniecia klawiszy
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

            //wylapywanie zwolnienia klawiszy
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

        //czyscimy ekran
        window.clear();
        
        //aktualizujemy cala gre
        update(frameClock.restart());

        //rysujemy wszystkie elementy
        window.setView(myView);
        window.draw(mojaMapa);
        window.draw(mojePrzeszkody);
        potwory.drawOgrs(window);
        potwory.drawMonstersHP(window);
        window.draw(player);
        drawUI();

        //wyswietlamy gotowa klatke 
        window.display();
    }
}

