//
// Created by Георгий Кузнецов on 24.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_RESOURCES_H_
#define ENGINE_LOGIC_LOGIC_INC_RESOURCES_H_
#define _USE_MATH_DEFINES

#include <memory>
#include <numeric>
#include <math.h>
#include <random>

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = M_PI;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double(double min = 0.0, double max = 1.0) {
  // Returns a random real in [min,max).
  std::random_device r;
  static std::uniform_real_distribution<double> distribution(min, max);
  static std::mt19937 generator(r());
  return distribution(generator);
}

inline double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

// includes
#include "ray.h"
#include "vec3.h"
#include "material.h"
//#include "sphere.h"
//#include "triangle.h"
//#include "hittable_list.h"
//#include "hittable.h"

#endif //ENGINE_LOGIC_LOGIC_INC_RESOURCES_H_
