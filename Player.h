#ifndef PONGPONG_PLAYER_H
#define PONGPONG_PLAYER_H
#include "SFML/Graphics.hpp"


class Player {
public:
    Player(sf::Texture, sf::Vector2f);
    sf::Sprite &getSprite();
    Player();
    float getVelocity();
    int getPoints();
private:
    sf::Sprite sprite;
    float velocity;
    int points;
;
};


#endif //PONGPONG_PLAYER_H
