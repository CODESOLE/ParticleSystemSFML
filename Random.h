#pragma once
#include <cstdlib>
#include <ctime>

class Random
{
  public:
    static unsigned getRandInt(const unsigned &&);
    static float getRandFloat(const float &&);
    virtual ~Random();
};
