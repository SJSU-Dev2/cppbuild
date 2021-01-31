#pragma once

/// Remap a numeric value from one range to another.
///
/// Example 1:
///
///   value = 5
///   current_minimum = 0, current_maximum = 10
///   new_minimum = 0, new_maximum = 100
///   result = 50
/// ```
///                            50
///   |--------------------------------------------------|
///   0                        |                         100
///       _____________________/
///      /
///      |
///   |-----|
///   0  5  10
/// ```
///
/// Example 2:
///
///   value = 7
///   current_minimum = 0, current_maximum = 10
///   new_minimum = 100, new_maximum = 200
///   result = 170
///
/// ```
///                                                          170
///                      |--------------------------------------------------|
///                    100                                   |              200
///        __________________________________________________/
///       /
///       |
///   |-----|
///   0   7 10
/// ```
///
/// Mapping equation is as follows:
///
/// ```
///               /                    (max - min)     \_
///      value = | (value - min) x -------------------  | + new_min
///               \                (new_max - new_min) /
/// ```
///
/// @param value - the value that will be mapped to the new range
/// @param min - current minimum value that the value can reach
/// @param max - current maximum value that the value can reach
/// @param new_min - the new minimum value to scale and shift the old value to
/// @param new_max - the new maximum value to scale and shift the old value to
float Map(float value, float min, float max, float new_min, float new_max);
