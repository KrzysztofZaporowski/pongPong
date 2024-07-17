#ifndef PONGPONG_GAMECONTROLER_H
#define PONGPONG_GAMECONTROLER_H
#include "Player.h"
#include "Ball.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <vector>


class GameControler {
public:
    GameControler(sf::RenderWindow*);
    void bounceWindow();
    void collideWithPLayer();
    void updatePlayer();
    void updateBall();
    bool isPaused();
    void updatePaused(sf::Event);
    void checkForGoal();
    void draw();
    void endGame();
    void newGame();
private:
    Player player1;
    Player player2;
    Ball ball;
    sf::RenderWindow * window;
    bool paused;
    sf::Vector2f player1StartingPosition;
    sf::Vector2f player2StartingPosition;
    sf::Vector2f getRandomVelocity();
    int player1Points;
    int player2Points;
};


#endif //PONGPONG_GAMECONTROLER_H
