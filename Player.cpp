#include "Player.h"

Player::Player(sf::Texture texture, sf::Vector2f position) {
    sprite = sf::Sprite();
    sprite.setTexture(texture);
    sprite.setPosition(position);
    velocity = 0.25f;
    points = 0;
}

sf::Sprite & Player::getSprite() {
    return sprite;
}

Player::Player() {

}

float Player::getVelocity() {
    return velocity;
}

int Player::getPoints() {
    return points;
}


