#include "enemy.h"


Ogr::Ogr() {
    this->enemyHP = 50;
    this->enemyStartHP = 50;
    this->enemySpeed = 0.8;
    this->enemyStr = 2;
    this->enemyDef = 1;
    this->deadFlag = 0;

}

void Ogr::setSpriteTexture(sf::Texture& ogrTexture) {

    this->enemySprite.setTexture(ogrTexture);
    this->enemySprite.setPosition( getObjectPosition().x, getObjectPosition().y );
}

//wykrywanie kolizji miedzy graczze a potowrem
bool Enemy::checkPosition(Position position) {

    if(position.x +32 >= this->objectPosition.x && position.x <= this->objectPosition.x + 32
        &&
        position.y + 32 >= this->objectPosition.y && position.y <= this->objectPosition.y + 32)
        return true;
    else
        return false;
}

//ustawia potwora na zadanej pozycji (oraz jego teksture)
void Enemy::setEnemyPosition(float newXPosition, float newYPosition) {

        this->setObjectPosition(newXPosition, newYPosition);
        this->enemySprite.setPosition(newXPosition, newYPosition);

}

//funkcja wczytuje potowry z pliku oraz wczytuje ich teksture
void Monsters::loadOgrs(string fileOgrsPosition, string fileTextureOgr) {

    //ustawiam respawn wszystkich ogrow na 8 sekund
    this->ogrRespawnTime = sf::seconds(5); 

    //wczytuje texture ogra z pliku
    this->ogrTexture.loadFromFile("data/textures/" + fileTextureOgr);

    //otwieram plik ze startowymi pozycjami ogrow
    FILE* ogrFile;
    ogrFile = fopen(("data/" + fileOgrsPosition).c_str(), "r");


    //wczytaj z pliku ilosc ogrow na mapie
    unsigned int ogrCount;
    fscanf(ogrFile, "%d ", &ogrCount);


    //wczytauje z pliku pozycje startowe ogrow
    // i w vectorze ogrs tworze ogry o zadanych pozycjach
    Ogr tempOgr;
    Position tempPosition;
    for(size_t i = 0; i < ogrCount; ++i) {

        fscanf(ogrFile, "%f %f", &tempPosition.x, &tempPosition.y);
        tempOgr.setObjectPosition(tempPosition.x, tempPosition.y);
        tempOgr.setSpriteTexture(this->ogrTexture);
        tempOgr.setEnemyStartPosition(tempPosition.x, tempPosition.y);
        ogrs.push_back(tempOgr);
    }
}

//funkcja rysujaca zywe ogry
void Monsters::drawOgrs(sf::RenderWindow& window) {

    for(size_t i = 0; i < ogrs.size(); ++i)
        if(ogrs[i].checkEnemyDeadFlag() == 0 )
            window.draw(ogrs[i]);

}

//przeszukuje vector ogrow i sprawdza czy jest jakis na zadanej pozycji, jesli tak to zwraca go, jesli nie to zwraca NULL
Enemy* Monsters::getMonsterOnPosition(Position position) {

    for(size_t i = 0; i < ogrs.size(); ++i)
        if(ogrs[i].checkPosition(position))
            return &ogrs[i];

    return NULL;
}


//funkcja zwaraca pierwszego w pamieci potwora ktory jest w zasiegu ataku
Enemy* Monsters::getMonsterOnAtackArea(Position playerPosition, int attackDirection, float atackRange) {

    if(attackDirection == 0) {

        for(size_t i = 0; i < ogrs.size(); ++i) {
            if(playerPosition.y + 32 <= ogrs[i].getObjectPosition().y && playerPosition.y + 32 + atackRange >= ogrs[i].getObjectPosition().y
               &&
               playerPosition.x + 16 >= ogrs[i].getObjectPosition().x && playerPosition.x - 16 <= ogrs[i].getObjectPosition().x)
                    return &ogrs[i];
        }
    }


    else if(attackDirection == 1) {

        for(size_t i = 0; i < ogrs.size(); ++i) {
            if(playerPosition.x >= ogrs[i].getObjectPosition().x + 32 && playerPosition.x <= ogrs[i].getObjectPosition().x + 32 + atackRange
               &&
               playerPosition.y + 16 >= ogrs[i].getObjectPosition().y && playerPosition.y - 16 <= ogrs[i].getObjectPosition().y)
                    return &ogrs[i]; 
        }
    }


    else if(attackDirection == 2) {

        for(size_t i = 0; i < ogrs.size(); ++i) {
            if(playerPosition.x + 32 <= ogrs[i].getObjectPosition().x && playerPosition.x + 32 + atackRange >= ogrs[i].getObjectPosition().x
               &&
               playerPosition.y + 16 >= ogrs[i].getObjectPosition().y && playerPosition.y - 16 <= ogrs[i].getObjectPosition().y)
                    return &ogrs[i]; 
        }
    }


    else if(attackDirection == 3) {

        for(size_t i = 0; i < ogrs.size(); ++i) {
            if(playerPosition.y >= ogrs[i].getObjectPosition().y + 32 && playerPosition.y  <= ogrs[i].getObjectPosition().y + 32 + atackRange
               &&
               playerPosition.x + 16 >= ogrs[i].getObjectPosition().x && playerPosition.x - 16 <= ogrs[i].getObjectPosition().x)
                    return &ogrs[i];
        }
    }

    return NULL;
}

//funkcja aktualizuje potwory - usmierca te co maja < 0 HP, daje exp dla gracza za zabicie potowra, respawnuje potwory
void Monsters::updateDeadMonsters(sf::Time mainClockTime, Player& player) {

    //usmiercanie mobka
    for(size_t i = 0; i < ogrs.size(); ++i)
        if(ogrs[i].getEnemyHP() <= 0 && ogrs[i].checkEnemyDeadFlag() == 0) {
            ogrs[i].setEnemyPosition(-40, -40);
            ogrs[i].setEnemyDeadFlag(1);
            ogrs[i].setDeathTime(mainClockTime);


            player.setPlayerExp(player.getPlayerExp() + this->ogrExp );

            if(player.getPlayerExp() >= player.getPlayerLvl() * 100) {
                player.setPlayerLvl(player.getPlayerLvl() + 1);
                player.setPlayerExp(0);
                
            }
        }


    //respawn ogrow
    for(size_t i = 0; i < ogrs.size(); ++i)
        if(ogrs[i].checkEnemyDeadFlag() == 1) {
           // printf("%f %f %f\n", mainClockTime.asSeconds(), ogrs[i].getDeathTime().asSeconds(), ogrRespawnTime.asSeconds());
               
            if(mainClockTime - ogrs[i].getDeathTime() > ogrRespawnTime) {
                ogrs[i].setEnemyPosition(ogrs[i].getEnemyStartPosition().x, ogrs[i].getEnemyStartPosition().y);
                ogrs[i].setEnemyDeadFlag(0);
                ogrs[i].setEnemyHP(ogrs[i].getEnemyStartHP());
            }
        }
}


//funkcja rysujaca nad potoworami ich paski HP
void Monsters::drawMonstersHP(sf::RenderWindow& window) {

    sf::RectangleShape lineHP;

    for(size_t i = 0; i < ogrs.size(); ++i)
        if(ogrs[i].checkEnemyDeadFlag() == 0) {

            lineHP.setSize(sf::Vector2f(32, 3));
            lineHP.setFillColor(sf::Color(0, 0, 0));
            lineHP.setPosition(sf::Vector2f(ogrs[i].getObjectPosition().x, ogrs[i].getObjectPosition().y));
            window.draw(lineHP);

            lineHP.setSize(sf::Vector2f(32 * ogrs[i].getEnemyHP() / ogrs[i].getEnemyStartHP(), 3));
            lineHP.setFillColor(sf::Color(255, 0, 0));
            window.draw(lineHP);

        }
}