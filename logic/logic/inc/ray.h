#ifndef ENGINE_LOGIC_LOGIC_INC_RAY_H_
#define ENGINE_LOGIC_LOGIC_INC_RAY_H_

#include "vec3.h"

class ray {
 public:
  ray(const point3& origin, const vec3& direction);

  [[nodiscard]] point3 origin() const;
  [[nodiscard]] vec3 direction() const;

  [[nodiscard]] point3 at(double t) const;

  ~ray();
 public:
  point3 orig;
  vec3 dir;
};

#endif //ENGINE_LOGIC_LOGIC_INC_RAY_H_
