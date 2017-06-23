#include <cstdio>
#include <SFML/Graphics.hpp>
#include "main.h"
#include <string>
#include <vector>

using namespace std;

#ifndef OBSTACLE
#define OBSTACLE


class Obstacle : public Object {

    int textureNumber;
    
public:

    Obstacle(int textureNumber) { this->textureNumber = textureNumber; }

    //funkcja ustwia danej przeszkodzie numer tekstury
    void setObstacleTextureNumber(int textureNumber) { this->textureNumber = textureNumber; }
    int getObstacleTextureNumber() { return this->textureNumber; }
    
    //wykrywa kolizje miedzy pozycja tej przeszkody, a zadana pozycja position, jesli jest kolizja zwraca true, jesli nie false
    bool checkPosition(Position position);

};





class Obstacles : public sf::Drawable {

    vector <Obstacle> obstaclesVector;
    unsigned int obstaclesCount;
    sf::VertexArray obstaclesVertices;
    sf::Texture obstaclesTexture;

    //funckja pozwala wyswietlic przeszkody w glownej petli gry
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &obstaclesTexture;
        target.draw(obstaclesVertices, states);
    }

public:

    //funkcja przeszukuje caly vector przeszkod w poszukiwaniu czy istnieje przeszkoda na zadanej pozycji, jeśli tak to ja zwraca, jesli nie to zwraca NULL
    Obstacle* getObstacleOnPosition(Position position);

    //funkcja wczytuje z pliku teksture przeszkod oraz wczytuje przeszkody do vectora i przetwarza je (tak jak w Map)
    void loadObstacles(string fileObstacles, string fileTextureObstcles, sf::Vector2u textureSize);
};

#endif

