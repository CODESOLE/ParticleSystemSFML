#include "Particle.h"
#include "Random.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/WindowStyle.hpp>

int main()
{
    unsigned fps = 60;
    sf::ContextSettings ctx;
    ctx.antialiasingLevel = 8;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!",sf::Style::Default,ctx);
    window.setFramerateLimit(fps);
    ParticleSystem p1{1.0f, 60};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        p1.OnParticleUpdate(sf::Mouse::getPosition(window), fps);

        window.clear();
        for (auto &sprts : p1.getParticles())
            window.draw(sprts);
        window.display();
    }

    return 0;
}
