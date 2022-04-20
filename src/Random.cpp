#include "Random.h"

unsigned Random::getRandInt(const unsigned &&range = RAND_MAX)
{
    return std::rand()/((RAND_MAX + 1u)/range);
}

float Random::getRandFloat(const float &&range = (float)RAND_MAX)
{
    return range * ((float)std::rand() / (float)RAND_MAX);
}

Random::~Random()
{
}
