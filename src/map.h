#include <string>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

#ifndef MAP
#define MAP

class Map : public sf::Drawable { 

    unsigned int mapHeight, mapWidth;
    unsigned int* tileMatrix;
    sf::VertexArray mapVertices;
    sf::Texture tileSet;

    //ta funkcja potrzebna do wyswietlania mapy z glownej petli
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &tileSet;
        target.draw(mapVertices, states);
    }

public:


//funkcja wczytuje mape z pliku
void loadMap(string fileMap, string fileTextureMap, sf::Vector2u tileSize);


};

#endif
