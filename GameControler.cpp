#include "GameControler.h"

GameControler::GameControler(sf::RenderWindow * _window) {
    sf::Image image;
    image.create(15, 200, sf::Color::White);
    sf::Texture * texture = new sf::Texture();
    if (!texture->loadFromImage(image)) {
        std::perror("Unable to load texture.");
    }
    player1StartingPosition = sf::Vector2f (20, 310);
    player2StartingPosition = sf::Vector2f (1045, 310);
    player1 = Player(*texture, player1StartingPosition);
    player2 = Player(*texture, player2StartingPosition);
    ball = Ball(getRandomVelocity());
    window = _window;
    paused = false;
}

void GameControler::bounceWindow() {
    if (ball.getCircleShape().getPosition().y < 0 ||
            ball.getCircleShape().getPosition().y + ball.getCircleShape().getRadius() * 2 > 720)
        ball.inverseYVelocity();
}

void GameControler::collideWithPLayer() {
    if (ball.getCircleShape().getGlobalBounds().intersects(player1.getSprite().getGlobalBounds())) {
        ball.bounce(player1.getSprite().getPosition().x + player1.getSprite().getGlobalBounds().width);
        //ball.resetVelocity(getRandomVelocity());
    }
    if (ball.getCircleShape().getGlobalBounds().intersects(player2.getSprite().getGlobalBounds())) {
        ball.bounce(player2.getSprite().getPosition().x - ball.getCircleShape().getRadius() * 2);
        //ball.resetVelocity(getRandomVelocity());
    }

}

void GameControler::updatePlayer() {
    sf::Vector2f velocityDown(0, player1.getVelocity());
    sf::Vector2f velocityUp(0, -player1.getVelocity());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1.getSprite().getPosition().y > 0){
        player1.getSprite().move(velocityUp);
        //printf("%f - %f\n", player1.getSprite().getPosition().x, player1.getSprite().getPosition().y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player1.getSprite().getPosition().y < 520)
        player1.getSprite().move(velocityDown);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2.getSprite().getPosition().y > 0)
        player2.getSprite().move(velocityUp);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2.getSprite().getPosition().y < 520)
        player2.getSprite().move(velocityDown);
}

void GameControler::updateBall() {
    ball.move();
}

sf::Vector2f GameControler::getRandomVelocity() {
    std::vector<sf::Vector2f> startVelocities = {
            {0.1f, 0.1f},
            {-0.1f, 0.1f},
            {0.1f, -0.1f},
            {-0.1f, -0.1f},
            {0.25f, 0.1f},
            {0.1f, 0.25f},
            {-0.25f, 0.1f},
            {0.25f, -0.1f},
            {-0.25f, -0.1f},
            {-0.1f, 0.25f},
            {0.1f, -0.25f},
            {-0.1f, -0.25f}
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    int index = std::uniform_int_distribution<>(0, startVelocities.size() - 1)(gen);
    return startVelocities[index];
}

bool GameControler::isPaused() {
    return paused;
}

void GameControler::updatePaused(sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
            paused = !paused;
}

void GameControler::checkForGoal() {
    //Goal for player2
    if (ball.getCircleShape().getPosition().x < 0) {
        player1.getSprite().setPosition(player1StartingPosition);
        player2.getSprite().setPosition(player2StartingPosition);
        ball.setStartingPosition();
        ball.resetVelocity();
        sf::Vector2f nextVelocity(-ball.getVelocity().x, ball.getVelocity().y);
        ball.setVelocity(nextVelocity);
    }
    //Goal for player1
    if (ball.getCircleShape().getPosition().x + ball.getCircleShape().getRadius() * 2 > 1080) {
        player1.getSprite().setPosition(player1StartingPosition);
        player2.getSprite().setPosition(player2StartingPosition);
        ball.setStartingPosition();
        ball.resetVelocity();
    }
}

void GameControler::draw() {
    window->draw(player1.getSprite());
    window->draw(player2.getSprite());
    window->draw(ball.getCircleShape());
}
