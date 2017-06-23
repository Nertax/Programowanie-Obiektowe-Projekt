#include <SFML/Graphics.hpp>
#include "main.h"
#include "player.h"
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
    sf::Sprite enemySprite;

public:

    //wykrywanie kolizji miedzy graczze a potowrem
    bool checkPosition(Position position);

    //ustawia potwora na zadanej pozycji (oraz jego teksture)
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



class Monsters {

    vector <Ogr> ogrs;
    sf::Time ogrRespawnTime;
    sf::Texture ogrTexture;
    int ogrExp;

public:

    Monsters() { this->ogrExp = 50; }

    //przeszukuje vector ogrow i sprawdza czy jest jakis na zadanej pozycji, jesli tak to zwraca go, jesli nie to zwraca NULL
    Enemy* getMonsterOnPosition(Position position);

    //funkcja zwaraca pierwszego w pamieci potwora ktory jest w zasiegu ataku
    Enemy* getMonsterOnAtackArea(Position playerPosition, int attackDirection, float atackRange);

    //funkcja wczytuje potowry z pliku oraz wczytuje ich teksture
    void loadOgrs(string fileOgrsPosition, string fileTextureOgr);

    //funkcja rysujaca zywe ogry
    void drawOgrs(sf::RenderWindow& window);

    //funkcja aktualizuje potwory - usmierca te co maja < 0 HP, daje exp dla gracza za zabicie potowra, respawnuje potwory
    void updateDeadMonsters(sf::Time mainClockTime, Player& player);

    //funkcja rysujaca nad potoworami ich paski HP
    void drawMonstersHP(sf::RenderWindow& window);

};

#endif
