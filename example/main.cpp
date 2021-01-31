#include <array>
#include <cstdio>

#include "average.hpp"
#include "map.hpp"

int main()
{
  std::array<float, 5> samples = { 1.2f, 5.2f, 4.5f, 8.8f, 9.4f };
  float average_value          = Average(samples);
  float scale_to_100           = Map(average_value, 0, 10, 0, 100);

  printf("average = %f --> scaled = %f\n", average_value, scale_to_100);

  return 0;
}