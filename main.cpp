#include "Particle.h"
#include "Random.h"
#include "imgui-sfml/imgui-SFML.h"
#include "imgui/imgui.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <utility>

int main()
{
    unsigned fps = 60;
    sf::ContextSettings ctx;
    ctx.antialiasingLevel = 8;
    std::srand(std::time(nullptr));
    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!", sf::Style::Default, ctx);
    window.setFramerateLimit(fps);
    ImGui::SFML::Init(window);
    ParticleSystem p1{0.0f};
    sf::Clock deltaClock;
    float noise = 1.f, pLT = 1.f;
    sf::Vector2f beginS{10.f, 10.f}, endS{20.f, 20.f};
    int bc[3] = {255, 0, 0}, ec[3] = {0, 0, 255};
    sf::Color beginC{(sf::Uint8)bc[0], (sf::Uint8)bc[1], (sf::Uint8)bc[2]},
        endC{(sf::Uint8)ec[0], (sf::Uint8)ec[1], (sf::Uint8)ec[2]};

    while (window.isOpen())
    {
        beginC.r = (sf::Uint8)bc[0];
        beginC.g = (sf::Uint8)bc[1];
        beginC.b = (sf::Uint8)bc[2];
        endC.r = (sf::Uint8)ec[0];
        endC.g = (sf::Uint8)ec[1];
        endC.b = (sf::Uint8)ec[2];
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        p1.setNoisePower(std::move(noise));
        p1.setParticalLifeTime(std::move(pLT));
        p1.setBeginEndColor(std::move(beginC), std::move(endC));
        p1.setBeginEndSize(sf::Vector2f{10.f, 10.f}, sf::Vector2f{20.f, 20.f});

        p1.OnParticleUpdate(sf::Mouse::getPosition(window), fps);

        ImGui::Begin("Particle System Control Panel");
        ImGui::SliderFloat("Noise Multiplier: ", &noise, 1.f, 5.f, "%.2f", 1.0f);
        ImGui::SliderFloat("Particle Life Time: ", &pLT, 0.2f, 3.f, "%.2f", 0.5f);
        ImGui::SliderInt3("Begin Color: ", &bc[0], 0, 255);
        ImGui::SliderInt3("End Color: ", &ec[0], 0, 255);
        ImGui::End();

        window.clear();
        for (auto &sprts : p1.getParticles())
            window.draw(sprts);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
