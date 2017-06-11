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

    void setObstacleTextureNumber(int textureNumber) { this->textureNumber = textureNumber; }

    int getObstacleTextureNumber() { return this->textureNumber; }

    bool checkPosition(Position position);

};





class Obstacles : public sf::Drawable {

    vector <Obstacle> obstaclesVector;
    unsigned int obstaclesCount;
    sf::VertexArray obstaclesVertices;
    sf::Texture obstaclesTexture;

    //ta funkcja konieczna, znaleziona w tutorialach do sfmla
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = &obstaclesTexture;
        target.draw(obstaclesVertices, states);
    }

public:

    Obstacle* getObstacleOnPosition(Position position);

    void loadObstacles(string fileObstacles, string fileTextureObstcles, sf::Vector2u textureSize);

    

};

#endif

