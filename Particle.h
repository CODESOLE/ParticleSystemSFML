#pragma once

#include "Random.h"
#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

struct particle
{
    particle(const sf::Vector2i &_pos, const sf::Vector2f &&_dir) : pos(_pos), dir(_dir)
    {
        rect.setSize(beginSize);
        rect.setPosition((sf::Vector2f)pos);
        rect.setOrigin({beginSize.x / 2.f, beginSize.y / 2.f});
        rect.setFillColor(beginColor);
    }
    void translate()
    {
        rect.move(dir);
    }
    void scale()
    {
        rect.scale(scaleFactor);
    }
    void rotate()
    {
        if (rotSide == 0)
            rect.rotate(rotateFactor);
        else
            rect.rotate(-rotateFactor);
    }

    float rotateFactor = 6.f;
    sf::Vector2f scaleFactor = {1.03f, 1.03f}, dir{0.f, 0.f};
    sf::RectangleShape rect;
    int rotSide = Random::getRandInt(2);
    sf::Clock clk;
    static sf::Vector2f beginSize, endSize;
    static sf::Color beginColor, endColor;
    sf::Vector2i pos = {0, 0};
    sf::Uint8 red, green, blue;
    unsigned alpha = 255, r{(unsigned)std::abs(endColor.r - beginColor.r)},
             g{(unsigned)std::abs(endColor.g - beginColor.g)}, b{(unsigned)std::abs(endColor.b - beginColor.b)};
};

class ParticleSystem
{
  public:
    ParticleSystem() = delete;
    ParticleSystem(const float &&pLF);
    ParticleSystem(const float &pLF);
    void OnParticleUpdate(const sf::Vector2i &, unsigned &);
    void setNoisePower(const float &&);
    void setBeginEndColor(sf::Color &&, sf::Color &&);
    void setBeginEndSize(sf::Vector2f &&, sf::Vector2f &&);
    void setParticalLifeTime(const float &&);
    std::vector<sf::RectangleShape> &getParticles();

  private:
    const unsigned pCount = 999;
    float noisePower = 1.f;
    std::vector<particle> sprites;
    float particleLifeTime = 1.f;
};
