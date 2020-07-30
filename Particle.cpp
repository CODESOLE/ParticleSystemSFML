#include "Particle.h"
#include "Random.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

ParticleSystem::ParticleSystem(const float &&pLF, const unsigned &&pool) : particleLifeTime(pLF), pCount(pool)
{
    if (pCount <= 1)
        pCount = 2;
    sprites.reserve(pCount);
}

void ParticleSystem::OnParticleUpdate(const sf::Vector2i &mousePos, unsigned &fps)
{
    if (sprites.size() < pCount)
        sprites.push_back(
            particle{mousePos, {(Random::getRandFloat(1.f) - 0.5f) * 3.f, (Random::getRandFloat(1.f) - 0.5f) * 3.f}});
    for (std::size_t i{0}; i < sprites.size(); ++i)
    {
        if (sprites[i].clk.getElapsedTime() > sf::seconds(particleLifeTime))
            sprites.erase(sprites.begin() + i);
        if (sprites[i].alpha < 4.f)
            sprites[i].alpha = 0.f;
        else
            sprites[i].alpha -= (float)255 / ((float)fps * particleLifeTime);

        // if (sprites[i].beginColor.r < sprites[i].endColor.r)
        //     sprites[i].r += (float)sprites[i].r / ((float)fps * particleLifeTime);
        // else
        //     sprites[i].r -= (float)sprites[i].r / ((float)fps * particleLifeTime);

        // std::cout << (unsigned)sprites[0].rect.getFillColor().a << std::endl;
        sprites[i].rect.setFillColor(sf::Color{
            (sf::Uint8)(sprites[i].rect.getFillColor().r + ((float)sprites[i].r / ((float)fps * particleLifeTime))),
            (sf::Uint8)(sprites[i].rect.getFillColor().g + ((float)sprites[i].g / ((float)fps * particleLifeTime))),
            (sf::Uint8)(sprites[i].rect.getFillColor().b + ((float)sprites[i].b / ((float)fps * particleLifeTime))),
            (sf::Uint8)sprites[i].alpha});
        sprites[i].translate();
        sprites[i].rotate();
        if (sprites[i].rect.getSize() < sprites[i].endSize)
            sprites[i].scale();
    }
}

std::vector<sf::RectangleShape> &ParticleSystem::getParticles()
{
    static std::vector<sf::RectangleShape> shapes;
    shapes.reserve(pCount);
    shapes.clear();
    for (auto &sp : sprites)
        shapes.push_back(sp.getRect());
    return shapes;
}
