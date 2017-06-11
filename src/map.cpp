#include "map.h"

void Map::loadMap(string fileMap, string fileTextureMap, sf::Vector2u tileSize) {

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

