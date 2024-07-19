#ifndef PONGPONG_BALL_H
#define PONGPONG_BALL_H
#include "SFML/Graphics.hpp"


class Ball {
public:
    Ball();
    Ball(sf::Vector2f);
    void resetVelocityFactor();
    sf::CircleShape & getCircleShape();
    void inverseYVelocity();
    void bounce(float);
    void setStartingPosition();
    void move();
    void setVelocity(sf::Vector2f);
    const sf::Vector2f &getVelocity() const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f position;
    float velocityFactor{};
    sf::Vector2f startingVelocity;
};


#endif //PONGPONG_BALL_H
