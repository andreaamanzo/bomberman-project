#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>
#include <ctime>

namespace Random
{
  static const int _ = [](){ 
    std::srand(static_cast<unsigned int>(std::time(0)));
    return 0; 
  }();

  inline int get(int min, int max)
	{
    return (min + std::rand() % (max + 1 - min));
	}
}

#endif