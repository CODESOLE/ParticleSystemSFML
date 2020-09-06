#include "Particle.h"
#include "Random.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

sf::Color particle::beginColor{255, 0, 0, 255};
sf::Color particle::endColor{0, 0, 255, 255};
sf::Vector2f particle::beginSize{20.f, 20.f};
sf::Vector2f particle::endSize{30.f, 30.f};

ParticleSystem::ParticleSystem(const float &&pLF) : particleLifeTime(pLF)
{
    if (particleLifeTime <= 0.f)
        particleLifeTime = 1.f;
    sprites.reserve(pCount);
}

ParticleSystem::ParticleSystem(const float &pLF) : particleLifeTime(pLF)
{
    if (particleLifeTime <= 0.f)
        particleLifeTime = 1.f;
    sprites.reserve(pCount);
}

void ParticleSystem::OnParticleUpdate(const sf::Vector2i &mousePos, unsigned &fps)
{
    if (sprites.size() < pCount)
        sprites.push_back(particle{
            mousePos,
            {(Random::getRandFloat(1.f) - 0.5f) * noisePower, (Random::getRandFloat(1.f) - 0.5f) * noisePower}});
    for (std::size_t i{0}; i < sprites.size(); ++i)
    {
        if (sprites[i].clk.getElapsedTime() > sf::seconds(particleLifeTime))
            sprites.erase(sprites.begin() + i);
        if (sprites[i].alpha < 15.f)
            sprites[i].alpha = 0.f;
        else
            sprites[i].alpha -= (float)255 / ((float)fps * particleLifeTime);

        if (sprites[i].beginColor.r < sprites[i].endColor.r)
        {
            sprites[i].red =
                (sf::Uint8)(sprites[i].rect.getFillColor().r + ((float)sprites[i].r / ((float)fps * particleLifeTime)));
        }
        else
        {
            sprites[i].red =
                (sf::Uint8)(sprites[i].rect.getFillColor().r - ((float)sprites[i].r / ((float)fps * particleLifeTime)));
        }
        if (sprites[i].beginColor.g < sprites[i].endColor.g)
        {
            sprites[i].green =
                (sf::Uint8)(sprites[i].rect.getFillColor().g + ((float)sprites[i].g / ((float)fps * particleLifeTime)));
        }
        else
        {
            sprites[i].green =
                (sf::Uint8)(sprites[i].rect.getFillColor().g - ((float)sprites[i].g / ((float)fps * particleLifeTime)));
        }
        if (sprites[i].beginColor.b < sprites[i].endColor.b)
        {
            sprites[i].blue =
                (sf::Uint8)(sprites[i].rect.getFillColor().b + ((float)sprites[i].b / ((float)fps * particleLifeTime)));
        }
        else
        {
            sprites[i].blue =
                (sf::Uint8)(sprites[i].rect.getFillColor().b - ((float)sprites[i].b / ((float)fps * particleLifeTime)));
        }

        sprites[i].rect.setFillColor(
            sf::Color{sprites[i].red, sprites[i].green, sprites[i].blue, (sf::Uint8)sprites[i].alpha});
        sprites[i].translate();
        sprites[i].rotate();
        if ((sprites[i].rect.getSize().x < sprites[i].endSize.x) &&
            (sprites[i].rect.getSize().y < sprites[i].endSize.y))
            sprites[i].scale();
    }
}

void ParticleSystem::setNoisePower(const float &&_noisePower)
{
    if (_noisePower <= 0.f)
    {
        noisePower = 1.f;
        return;
    }
    noisePower = _noisePower;
}

void ParticleSystem::setBeginEndColor(sf::Color &&begin, sf::Color &&end)
{
    particle::beginColor = std::move(begin);
    particle::endColor = std::move(end);
}

void ParticleSystem::setBeginEndSize(sf::Vector2f &&begin, sf::Vector2f &&end)
{
    particle::beginSize = std::move(begin);
    particle::endSize = std::move(end);
}

void ParticleSystem::setParticalLifeTime(const float &&_pLF)
{
    if (_pLF <= 0.f)
    {
        particleLifeTime = 1.f;
        return;
    }
    particleLifeTime = std::move(_pLF);
}

std::vector<sf::RectangleShape> &ParticleSystem::getParticles()
{
    static std::vector<sf::RectangleShape> shapes;
    shapes.reserve(pCount);
    shapes.clear();
    for (auto &sp : sprites)
        shapes.push_back(sp.rect);
    return shapes;
}
