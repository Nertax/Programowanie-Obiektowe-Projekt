#include "obstacle.h"

//wykrywa kolizje miedzy pozycja tej przeszkody, a zadana pozycja position, jesli jest kolizja zwraca true, jesli nie false
bool Obstacle::checkPosition(Position position) {

    if(position.x +32 >= this->objectPosition.x && position.x <= this->objectPosition.x + 32
        &&
        position.y + 32 >= this->objectPosition.y && position.y <= this->objectPosition.y + 32)
        return true; 
    else
        return false;
}

//funkcja przeszukuje caly vector przeszkod w poszukiwaniu czy istnieje przeszkoda na zadanej pozycji, jeśli tak to ja zwraca, jesli nie to zwraca NULL
Obstacle* Obstacles::getObstacleOnPosition(Position position) {

    for(size_t i = 0; i < obstaclesVector.size(); ++i)
        if(obstaclesVector[i].checkPosition(position))
            return &obstaclesVector[i];

    return NULL;
}


//funkcja wczytuje z pliku teksture przeszkod oraz wczytuje przeszkody do vectora i przetwarza je (tak jak w Map)
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


