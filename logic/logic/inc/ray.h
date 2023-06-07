#ifndef ENGINE_LOGIC_LOGIC_INC_RAY_H_
#define ENGINE_LOGIC_LOGIC_INC_RAY_H_

#include "vec3.h"

class ray {
 public:
  ray();
  ray(const point3& origin, const vec3& direction, double time = 0.0);

  [[nodiscard]] point3 origin() const;
  [[nodiscard]] vec3 direction() const;

  [[nodiscard]] point3 at(double t) const;
  [[nodiscard]] double get_time() const;

  ~ray();
 public:
  point3 orig;
  vec3 dir;
  double time;
};

#endif //ENGINE_LOGIC_LOGIC_INC_RAY_H_
