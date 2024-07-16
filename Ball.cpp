#include "Ball.h"

Ball::Ball(sf::Vector2f _velocity) {
    shape = sf::CircleShape(10.f);
    position = sf::Vector2f (540.f, 360.f);
    velocity = _velocity;
    velocityFactor = 1;
    startingVelocity = _velocity;
}

void Ball::resetVelocity() {
    velocityFactor = 1;
    velocity = startingVelocity;
}

sf::CircleShape & Ball::getCircleShape() {
    return shape;
}

void Ball::inverseYVelocity() {
    velocity = sf::Vector2f (velocity.x, -velocity.y);
}

void Ball::bounce(float bouncePosition) {
    velocityFactor *= 1.1;
    velocity = sf::Vector2f (-velocityFactor * velocity.x, velocity.y);
    shape.setPosition(bouncePosition, shape.getPosition().y);
}

void Ball::setStartingPosition() {
    shape.setPosition(position);
}

Ball::Ball() {

}

void Ball::move() {
    shape.move(velocity);
}

void Ball::setVelocity(sf::Vector2f _velocity) {
    velocity = _velocity;
}

const sf::Vector2f &Ball::getVelocity() const {
    return velocity;
}
