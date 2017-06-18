#include <SFML/Graphics.hpp>
#include "main.h"
#include <vector>
#include <string>

using namespace std;

#ifndef ENEMY
#define ENEMY

class Enemy : public Object {

protected:
    int enemyHP;
    int enemyStartHP;
    float enemySpeed;
    int enemyStr;
    int enemyDef; 
    bool deadFlag;
    sf::Time deathTime;
    Position startPosition;
   // ActiveDirection playerMovement;
    sf::Sprite enemySprite;
  //  sf::Vector2u playerTexturePosition;
public:

    bool checkPosition(Position position);
    void setEnemyPosition(float newXPosition, float newYPosition);
    void setEnemyStartPosition(float newXPosition, float newYPosition) { this->startPosition.x = newXPosition; this->startPosition.y = newYPosition; }
    void setEnemyHP(int newHP) { this->enemyHP = newHP; }
    int getEnemyStartHP() { return this->enemyStartHP; }
    Position getEnemyStartPosition() { return this->startPosition; }
    int getEnemyDef() { return this->enemyDef; }
    int getEnemyHP() { return this->enemyHP; }
    int getEnemyStr() { return this->enemyStr; }
    void setEnemyDeadFlag(bool value) { this->deadFlag = value; }
    bool checkEnemyDeadFlag() { return this->deadFlag; }
    void setDeathTime(sf::Time time) { this->deathTime = time; }
    sf::Time getDeathTime() { return this->deathTime; }
};

class Ogr : public Enemy, public sf::Drawable {

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(enemySprite, states);
    }


public:
    Ogr();
    void setSpriteTexture(sf::Texture& ogrTexture);

};

#endif

class Monsters {

    vector <Ogr> ogrs;
    sf::Time ogrRespawnTime;
    sf::Texture ogrTexture;

public:

    Enemy* getMonsterOnPosition(Position position);
    Enemy* getMonsterOnAtackArea(Position playerPosition, int attackDirection, float atackRange);
    void loadOgrs(string fileOgrsPosition, string fileTextureOgr);
    void drawOgrs(sf::RenderWindow& window);
    void updateDeadMonsters(sf::Time mainClockTime);

};

/*

levelowanie

animacje walki
atakowanie gracza przez moby
smierc gracza
poruszanie sie potworow - algorytm ruchu, animacja ruchu jak u gracza
................
w update:
czy ustawiony punkt koncowy, 
jesli tak
    przestaw mobka - zrob krok tak jak w player.move
jesli nie
    czy zmienna czasowa danego moba nakazuje juz mu sie ruszyc, 
        jesli nie, to nic nie rob
        jesli tak to losujemy kierunek poruszania, oraz odleglosc i wyznaczamy na tej podstawie punkt koncowy
..................

komentarze w kodzie zrobic

dokumentacja:
bardziej robudowany opis niz na gitgubie - co to jest, na czy polega gra, jak sie poruszac itd - funkcja projektu i instrukcja obslugi programu
co udalo sie zroic a czego juz nie zdazylem

przy uzyciu czego pisana
instrukcja instalacji biblioteki
opis jakie klasy sa i opis co maja i za co sa odpowiedzialne
hierarchia klas
info o komentarzach w kodzie
*/
