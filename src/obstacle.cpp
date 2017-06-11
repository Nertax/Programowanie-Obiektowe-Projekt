#include "obstacle.h"


    bool Obstacle::checkPosition(Position position) {

        if(position.x +32 >= this->objectPosition.x && position.x <= this->objectPosition.x + 32
           &&
           position.y + 32 >= this->objectPosition.y && position.y <= this->objectPosition.y + 32)
            return true; //dokladniejsze wykrywanie kolizji
        else
            return false;
    }


    Obstacle* Obstacles::getObstacleOnPosition(Position position) {

        for(size_t i = 0; i < obstaclesVector.size(); ++i)
            if(obstaclesVector[i].checkPosition(position))
                return &obstaclesVector[i];

        return NULL;


    }

void Obstacles::loadObstacles(string fileObstacles, string fileTextureObstcles, sf::Vector2u textureSize) {

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


