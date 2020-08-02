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
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>

int main()
{
    unsigned fps = 60;
    sf::ContextSettings ctx;
    ctx.antialiasingLevel = 8;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!", sf::Style::Default, ctx);
    window.setFramerateLimit(fps);
    ParticleSystem p1{0.0f};
    bool change = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                change = !change;
            if (change)
            {
                p1.setNoisePower(3.f);
                p1.setParticalLifeTime(0.5f);
                p1.setBeginEndColor(sf::Color{0, 0, 255}, sf::Color{255, 0, 0});
                p1.setBeginEndSize(sf::Vector2f{10.f, 10.f}, sf::Vector2f{20.f, 20.f});
            }
            else
            {
                p1.setNoisePower(2.f);
                p1.setParticalLifeTime(1.f);
                p1.setBeginEndColor(sf::Color{255, 0, 0}, sf::Color{0, 0, 255});
                p1.setBeginEndSize(sf::Vector2f{20.f, 20.f}, sf::Vector2f{30.f, 30.f});
            }
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
