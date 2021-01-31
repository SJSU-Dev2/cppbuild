#include "map.hpp"

float Map(float value, float min, float max, float new_min, float new_max)
{
  float range_ratio = (new_max - new_min) / (max - min);
  float mapped      = ((value - min) * range_ratio) + new_min;

  return mapped;
};