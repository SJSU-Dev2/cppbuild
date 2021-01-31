#include "average.hpp"

float Average(std::span<float> array)
{
  float sum = 0;

  for (const auto & element : array)
  {
    sum += element;
  }

  return sum / array.size();
}
