#include <iostream>
#include <vector>
#include <random>
#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Ping Pong", sf::Style::Titlebar | sf::Style::Close);
    sf::Image image;
    image.create(15, 200, sf::Color::White);
    sf::CircleShape ball(10.f);
    ball.setPosition(540.f, 360.f);

    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cerr << "Unable to load texture" << std::endl;
        return 1;
    }

    sf::Sprite player1;
    player1.setTexture(texture);

    sf::Sprite player2;
    player2.setTexture(texture);

    sf::Vector2f player1Position(20, 310);
    sf::Vector2f player2Position(1045, 310);
    player1.setPosition(player1Position);
    player2.setPosition(player2Position);

    sf::Vector2f velocityUp(0, -0.25f);
    sf::Vector2f velocityDown(0, 0.25f);

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
    //initial velocity draw
    std::random_device rd;
    std::mt19937 gen(rd());
    int index = std::uniform_int_distribution<>(0, startVelocities.size() - 1)(gen);
    sf::Vector2f startVelocity(startVelocities[index]);
    sf::Vector2f player1PointVelocity = startVelocity;
    sf::Vector2f player2PointVelocity = startVelocity;
    if (startVelocity.x < 0){
        player1PointVelocity = startVelocity;
        player2PointVelocity = -startVelocity;
    }
    else{
        player1PointVelocity = -startVelocity;
        player2PointVelocity = startVelocity;
    }

    int player1Points = 0;
    int player2Points = 0;
    bool isPaused = false;

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
                isPaused = !isPaused;
        }

        if (!isPaused) {
            //Player1 movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player1.getPosition().y > 0)
                player1.move(velocityUp);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player1.getPosition().y < 520)
                player1.move(velocityDown);

            //Player2 movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player2.getPosition().y > 0)
                player2.move(velocityUp);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player2.getPosition().y < 520)
                player2.move(velocityDown);

            //Ball movement
            if (ball.getPosition().y < 0 || ball.getPosition().y + ball.getRadius() * 2 > 720)
                startVelocity.y = -startVelocity.y;

            if (ball.getGlobalBounds().intersects(player1.getGlobalBounds())) {
                startVelocity.x = -startVelocity.x;
                startVelocity.x = 1.1f * startVelocity.x;
                ball.setPosition(player1.getPosition().x + player1.getGlobalBounds().width, ball.getPosition().y);
            }
            if (ball.getGlobalBounds().intersects(player2.getGlobalBounds())) {
                startVelocity.x = -startVelocity.x;
                startVelocity.x = 1.1f * startVelocity.x;
                ball.setPosition(player2.getPosition().x - ball.getRadius() * 2, ball.getPosition().y);
            }

            //Ball comes off the window
            if (ball.getPosition().x < 0) {
                player1.setPosition(player1Position);
                player2.setPosition(player2Position);
                ball.setPosition(540.f, 360.f);
                startVelocity.x = player2PointVelocity.x;
                player2Points += 1;
                printf("Player 1 : %d\n", player1Points);
                printf("Player 2 : %d\n", player2Points);
            }
            if (ball.getPosition().x + ball.getRadius() * 2 > 1080) {
                player1.setPosition(player1Position);
                player2.setPosition(player2Position);
                ball.setPosition(540.f, 360.f);
                startVelocity.x = player1PointVelocity.x;
                player1Points += 1;
                printf("Player 1 : %d\n", player1Points);
                printf("Player 2 : %d\n", player2Points);
            }

            ball.move(startVelocity);
        }

        if (player1Points == 7 || player2Points == 7){
            isPaused = !isPaused;
            if (player1Points > player2Points)
                printf("PLayer 1 won\nFinal score\nPlayer 1 %d : Player 2 %d", player1Points, player2Points);
            else
                printf("PLayer 2 won\nFinal score\nPlayer 1 %d : Player 2 %d", player1Points, player2Points);
            printf("Press N to start new game");
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
            printf("New game\n");
            player1Points = 0;
            player2Points = 0;
            ball.setPosition(540.f, 360.f);
            player1.setPosition(player1Position);
            player2.setPosition(player2Position);
        }

        window.clear();
        window.draw(player1);
        window.draw(player2);
        window.draw(ball);
        window.display();
    }

    return 0;
}
