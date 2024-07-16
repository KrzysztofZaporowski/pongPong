#include "SFML/Graphics.hpp"
#include "GameControler.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Ping Pong", sf::Style::Titlebar | sf::Style::Close);

    GameControler gameControler(&window);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            gameControler.updatePaused(event); // przeniosłem to do pętli z tymi evenami i działa
        }

        if (gameControler.isPaused()) continue;
        gameControler.bounceWindow();
        gameControler.checkForGoal();
        gameControler.collideWithPLayer();
        gameControler.updateBall();
        gameControler.updatePlayer();

        window.clear();
        gameControler.draw();
        window.display();
    }

    return 0;
}
