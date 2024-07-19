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
    player1Points = player1.getPoints();
    player2Points = player2.getPoints();
}

void GameControler::bounceWindow() {
    if (ball.getCircleShape().getPosition().y < 0 ||
        ball.getCircleShape().getPosition().y + ball.getCircleShape().getRadius() * 2 > 720)
        ball.inverseYVelocity();
}

void GameControler::collideWithPLayer() {
    if (ball.getCircleShape().getGlobalBounds().intersects(player1.getSprite().getGlobalBounds())) {
        ball.bounce(player1.getSprite().getPosition().x + player1.getSprite().getGlobalBounds().width);
    }
    if (ball.getCircleShape().getGlobalBounds().intersects(player2.getSprite().getGlobalBounds())) {
        ball.bounce(player2.getSprite().getPosition().x - ball.getCircleShape().getRadius() * 2);
    }

}

void GameControler::updatePlayer() {
    sf::Vector2f velocityDown(0, player1.getVelocity());
    sf::Vector2f velocityUp(0, -player1.getVelocity());
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1.getSprite().getPosition().y > 0){
        player1.getSprite().move(velocityUp);
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
        player2Points += 1;
        printf("Player1 %d : Player2 %d\n", player1Points, player2Points);
    }
    //Goal for player1
    if (ball.getCircleShape().getPosition().x + ball.getCircleShape().getRadius() * 2 > 1080) {
        player1.getSprite().setPosition(player1StartingPosition);
        player2.getSprite().setPosition(player2StartingPosition);
        ball.setStartingPosition();
        ball.resetVelocity();
        player1Points += 1;
        printf("Player1 %d : Player2 %d\n", player1Points, player2Points);
    }
}

void GameControler::draw() {
    window->draw(player1.getSprite());
    window->draw(player2.getSprite());
    window->draw(ball.getCircleShape());
}

void GameControler::newGame() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
        player1.getSprite().setPosition(player1StartingPosition);
        player2.getSprite().setPosition(player2StartingPosition);
        ball.setStartingPosition();
        ball = Ball(getRandomVelocity());
        player1Points = player1.getPoints();
        player2Points = player2.getPoints();
        printf("New game.\n");
    }
}

void GameControler::endGame() {
    if (player1Points == 7){
        paused = true;
        printf("Congratulation player1. You won the game!\nFinal score: Player1 %d - Player2 %d\nGame will be restarted in 5 seconds\n"
                , player1Points, player2Points);
        player1.getSprite().setPosition(player1StartingPosition);
        player2.getSprite().setPosition(player2StartingPosition);
        ball.setStartingPosition();
        ball = Ball(getRandomVelocity());
        player1Points = player1.getPoints();
        player2Points = player2.getPoints();
        sf::sleep(sf::seconds(5));
        paused = false;
    }
    else if (player2Points == 7){
        paused = true;
        printf("Congratulation player2. You won the game!\nFinal score: Player1 %d - Player2 %d\nGame will be restarted in 5 seconds\n"
                , player1Points, player2Points);
        player1.getSprite().setPosition(player1StartingPosition);
        player2.getSprite().setPosition(player2StartingPosition);
        ball.setStartingPosition();
        ball = Ball(getRandomVelocity());
        player1Points = player1.getPoints();
        player2Points = player2.getPoints();
        sf::sleep(sf::seconds(5));
        paused = false;
    }
}

void GameControler::saveGameState() {
    std::ofstream outFile("game_state.txt");
    if (outFile.is_open()) {
        // Save player points
        outFile << player1Points << std::endl;
        outFile << player2Points << std::endl;

        // Save ball velocity
        outFile << ball.getVelocity().x << std::endl;
        outFile << ball.getVelocity().y << std::endl;

        outFile.close();
    } else {
        std::cerr << "Unable to open file for saving game state." << std::endl;
    }
}

void GameControler::loadGameState() {
    std::ifstream inFile("game_state.txt");
    if (inFile.is_open()) {
        // Load player points
        inFile >> player1Points;
        inFile >> player2Points;

        // Load ball velocity
        sf::Vector2f loadedVelocity;
        inFile >> loadedVelocity.x;
        inFile >> loadedVelocity.y;

        // Set ball velocity and reset the ball's position
        ball.setVelocity(loadedVelocity);
        ball.resetVelocity();

        inFile.close();
    } else {
        std::cerr << "Unable to open file for loading game state." << std::endl;
    }
}
