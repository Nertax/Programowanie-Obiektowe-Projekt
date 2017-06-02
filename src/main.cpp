#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

class Player;

struct Position {
    float x;
    float y;
};

struct ActiveDirection {
    bool up;
    bool left;
    bool right;
    bool down;
};

class Object {

protected:
    Position objectPosition;

public:
    Position getObjectPosition() { return this->objectPosition; }
    void setObjectPosition(float newXPosition, float newYPosition) { this->objectPosition.x = newXPosition; this->objectPosition.y = newYPosition; }
 
};

class Interact {

public: 

    void virtual interact(Player& player) = 0;

}; 

class Player : public Object, public sf::Drawable {

    int playerHP;
    float playerSpeed;
    ActiveDirection playerMovement;
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    sf::Vector2i playerTexturePosition;


    friend class Game;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(playerSprite, states);
    }


public:

Player() { 
    this->playerHP = 100;
    this->deactiveMovementDirection(0);
    this->deactiveMovementDirection(1);
    this->deactiveMovementDirection(2);
    this->deactiveMovementDirection(3);
    this->setObjectPosition(50 ,10);
    this->playerSprite.setPosition( getObjectPosition().x, getObjectPosition().y );
    this->playerSpeed = 1;
    this->playerTexturePosition.x = 1;
    this->playerTexturePosition.y = 0;
    playerTexture.loadFromFile("data/textures/player.png");
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));
    }

    void activeMovementDirection(int direction) {

        if(direction == 0)
            this->playerMovement.down = 1;

        if(direction == 1)
            this->playerMovement.left = 1;

        if(direction == 2)
            this->playerMovement.right = 1;

        if(direction == 3)
            this->playerMovement.up = 1;
    }

    void deactiveMovementDirection(int direction) {

        if(direction == 0)
            this->playerMovement.down = 0;

        if(direction == 1)
            this->playerMovement.left = 0;

        if(direction == 2)
            this->playerMovement.right = 0;

        if(direction == 3)
            this->playerMovement.up = 0;
    }

    void setPlayerPosition(float newXPosition, float newYPosition) {

        this->setObjectPosition(newXPosition, newYPosition);
        this->playerSprite.setPosition(newXPosition, newYPosition);

    }

    float getPlayerSpeed() { return this->playerSpeed; }


    Position getFuturePlayerPosition(int moveDirection) {

        Position temp = this->getObjectPosition();

        if(moveDirection == 0) 
            temp.y += playerSpeed;

        else if(moveDirection == 1)
            temp.x -= playerSpeed;

        else if(moveDirection == 2) 
            temp.x +=playerSpeed;

        else if(moveDirection == 3) 
            temp.y -= playerSpeed;  

        return temp;
    }

    void movePlayer(int moveDirection) {

        if(moveDirection == 0) {
            this->playerTexturePosition.y = 0;
            this->playerTexturePosition.x++;
            if(this->playerTexturePosition.x * 32 >= playerTexture.getSize().x)
                this->playerTexturePosition.x = 0;

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));

            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x, currentPosition.y += playerSpeed );
        }

        if(moveDirection == 1) {
            this->playerTexturePosition.y = 1;
            this->playerTexturePosition.x++;
            if(this->playerTexturePosition.x * 32 >= playerTexture.getSize().x)
                this->playerTexturePosition.x = 0;

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));


            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x -= playerSpeed, currentPosition.y );
        }

        if(moveDirection == 2) {
            this->playerTexturePosition.y = 2;
            this->playerTexturePosition.x++;
            if(this->playerTexturePosition.x * 32 >= playerTexture.getSize().x)
                this->playerTexturePosition.x = 0;

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));


            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x +=playerSpeed, currentPosition.y );
        }

        if(moveDirection == 3) {
            this->playerTexturePosition.y = 3;
            this->playerTexturePosition.x++;
            if(this->playerTexturePosition.x * 32 >= playerTexture.getSize().x)
                this->playerTexturePosition.x = 0;

            playerSprite.setTextureRect(sf::IntRect(playerTexturePosition.x * 32, playerTexturePosition.y * 32, 32, 32));


            Position currentPosition = this->getObjectPosition();
            this->setPlayerPosition( currentPosition.x, currentPosition.y -= playerSpeed );
        }
    }

};




class Obstacle : public Object {

    int textureNumber;
    
public:

    Obstacle(int textureNumber) { this->textureNumber = textureNumber; }

    void setObstacleTextureNumber(int textureNumber) { this->textureNumber = textureNumber; }

    int getObstacleTextureNumber() { return this->textureNumber; }

    bool checkPosition(Position position) {

        if(position.x +32 >= this->objectPosition.x && position.x <= this->objectPosition.x + 32
           &&
           position.y + 32 >= this->objectPosition.y && position.y <= this->objectPosition.y + 32)
            return true; //dokladniejsze wykrywanie kolizji
        else
            return false;
    }

};





class Obstacles : public sf::Drawable {

    vector <Obstacle> obstaclesVector;
    int obstaclesCount;
    sf::VertexArray obstaclesVertices;
    sf::Texture obstaclesTexture;

    //ta funkcja konieczna, znaleziona w tutorialach do sfmla
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &obstaclesTexture;
        target.draw(obstaclesVertices, states);
    }

public:

    Obstacle* getObstacleOnPosition(Position position) {

        for(size_t i = 0; i < obstaclesVector.size(); ++i)
            if(obstaclesVector[i].checkPosition(position))
                return &obstaclesVector[i];

        return NULL;


    }

void loadObstacles(string fileObstacles, string fileTextureObstcles, sf::Vector2u textureSize) {

    //otwieramy nasz plik z danymi do mapy
    FILE* obstacleFile;
    obstacleFile = fopen(("data/" + fileObstacles).c_str(), "r");

    //wczytaj z pliku ilosci obiektow
    fscanf(obstacleFile, "%d ", &obstaclesCount);
    
    //wczytujemy texture naszych przeszkod
    obstaclesTexture.loadFromFile("data/textures/" + fileTextureObstcles);

    //ustawiamy nasza kolekcje wierzcholkow
    obstaclesVertices.setPrimitiveType(sf::Quads);
    obstaclesVertices.resize(obstaclesCount * 4);

    //tworzymy nasza macierz kafelkow o odpowiednim rozmiarze
  //  tileMatrix = new unsigned int [mapWidth * mapHeight];

    //wczytujemy do vectora przeszkod nasze przeszkody
        Position tempPosition;
        int tempInt;
        Obstacle tempObstacle(-1);


    for(size_t i = 0; i < obstaclesCount; ++i) {
        fscanf(obstacleFile, "%d %f %f", &tempInt, &tempPosition.x, &tempPosition.y);
        tempObstacle.setObstacleTextureNumber(tempInt);
        tempObstacle.setObjectPosition(tempPosition.x, tempPosition.y);

        obstaclesVector.push_back(tempObstacle);
    }

        

    
    for (size_t i = 0; i < obstaclesVector.size(); ++i) {

            //pobieramy numer textury danej przeszkody
            int textureNumber = obstaclesVector[i].getObstacleTextureNumber();

            //znajdujemy teksture tej kafelki w zestawie tekstur
            int tu = textureNumber % (obstaclesTexture.getSize().x / textureSize.x);
            int tv = textureNumber / (obstaclesTexture.getSize().x / textureSize.x);

            // pobieramy adres koljenego kwadratu mapy
            sf::Vertex* quad = &obstaclesVertices[i * 4];

            //ustawiamy pozycje wierzcholkow naszych kwadratowych przeszkod
            quad[0].position = sf::Vector2f(obstaclesVector[i].getObjectPosition().x, obstaclesVector[i].getObjectPosition().y);
            quad[1].position = sf::Vector2f(obstaclesVector[i].getObjectPosition().x + textureSize.x, obstaclesVector[i].getObjectPosition().y);
            quad[2].position = sf::Vector2f(obstaclesVector[i].getObjectPosition().x + textureSize.x, obstaclesVector[i].getObjectPosition().y + textureSize.y);
            quad[3].position = sf::Vector2f(obstaclesVector[i].getObjectPosition().x, obstaclesVector[i].getObjectPosition().y + textureSize.y);

            //ustawiamy pozycje ich textur
            quad[0].texCoords = sf::Vector2f(tu * textureSize.x, tv * textureSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * textureSize.x, tv * textureSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * textureSize.x, (tv + 1) * textureSize.y);
            quad[3].texCoords = sf::Vector2f(tu * textureSize.x, (tv + 1) * textureSize.y);
        }


        fclose(obstacleFile);

    }

    

};





class Map : public sf::Drawable { 

    unsigned int mapHeight, mapWidth;
    unsigned int* tileMatrix;
    sf::VertexArray mapVertices;
    sf::Texture tileSet;

    //ta funkcja konieczna, znaleziona w tutorialach do sfmla
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &tileSet;
        target.draw(mapVertices, states);
    }

public:

void loadMap(string fileMap, string fileTextureMap, sf::Vector2u tileSize) {

    //otwieramy nasz plik z danymi do mapy
    FILE* mapFile;
    mapFile = fopen(("data/" + fileMap).c_str(), "r");

    //wczytaj z pliku wymiary mapy
    fscanf(mapFile, "%d %d ", &mapHeight, &mapWidth);
    
    //wczytujemy texture naszej kafelkowej mapy, ktora bedziamy nasza mape pokrywac
    tileSet.loadFromFile("data/textures/" + fileTextureMap);

    //ustawiamy nasza kolekcje wierzcholkow
    mapVertices.setPrimitiveType(sf::Quads);
    mapVertices.resize(mapWidth * mapHeight * 4);

    //tworzymy nasza macierz kafelkow o odpowiednim rozmiarze
    tileMatrix = new unsigned int [mapWidth * mapHeight];

    //wczytujemy do tej macierzy dane z pliku
    for(size_t i = 0; i < mapWidth * mapHeight; ++i)
        fscanf(mapFile, "%d ", &tileMatrix[i]);

    
    for (size_t i = 0; i < mapWidth; ++i)
        for (size_t j = 0; j < mapHeight; ++j) {

            //pobieramy numer kafelki na danej pozycji
            int tileNumber = tileMatrix[i + j * mapWidth];

            //znajdujemy teksture tej kafelki w zestawie tekstur
            int tu = tileNumber % (tileSet.getSize().x / tileSize.x);
            int tv = tileNumber / (tileSet.getSize().x / tileSize.x);

            // pobieramy adres koljenego kwadratu mapy
            sf::Vertex* quad = &mapVertices[(i + j * mapWidth) * 4];

            //ustawiamy pozycje jego wierzcholkow
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            //ustawiamy na nim texture
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }

        fclose(mapFile);

    }

};



class Game {

    Player player;
    enum playerMove { Down, Left, Right, Up };

    sf::RenderWindow window;
    sf::View myView;
    Map mojaMapa;
    Obstacles mojePrzeszkody;


public:

    Game() {


        window.create(sf::VideoMode(200, 200), "Decouyon Game");
        window.setFramerateLimit(59);
        window.setView(myView);

        myView.setCenter(player.getObjectPosition().x +16, player.getObjectPosition().y +16);
        myView.setSize(200, 200);

        mojaMapa.loadMap("mapDecuyon", "mapDecuyon.png", sf::Vector2u(32, 32));
        mojePrzeszkody.loadObstacles("obstaclesDecuyon", "obstaclesDecuyon.png", sf::Vector2u(32, 32));
    }



void update() {

        //aktualizujemy pozycje gracza
        if(player.playerMovement.down == 1) {
            Position futurePlayerPosition = player.getFuturePlayerPosition(0);
            Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

            if(temp == NULL) {
                player.movePlayer(0);
            }
        }

        if(player.playerMovement.left == 1) {
            Position futurePlayerPosition = player.getFuturePlayerPosition(1);
            Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

            if(temp == NULL) {
                player.movePlayer(1);
            }
        }

        if(player.playerMovement.right == 1) {
            Position futurePlayerPosition = player.getFuturePlayerPosition(2);
            Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

            if(temp == NULL) {
                player.movePlayer(2);
            }
        }

        if(player.playerMovement.up == 1) {
            Position futurePlayerPosition = player.getFuturePlayerPosition(3);
            Obstacle* temp = mojePrzeszkody.getObstacleOnPosition(futurePlayerPosition);

            if(temp == NULL) {
                player.movePlayer(3);
            }
        }

        myView.setCenter(player.getObjectPosition().x +16, player.getObjectPosition().y +16);
}

void runGame() {


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
        
        update();

        window.setView(myView);
        window.draw(mojaMapa);
        window.draw(mojePrzeszkody);
        window.draw(player);


        window.display();
    }




}







};




int main()
{
 
    Game mojaGra;
    mojaGra.runGame();




    return 0;
}


