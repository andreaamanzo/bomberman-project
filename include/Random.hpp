#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>

namespace Random
{
  inline int get(int min, int max)
	{
    return (min + std::rand() % (max + 1 - min));
	}
}

#endif