#ifndef ENGINE_LOGIC_LOGIC_INC_RAY_H_
#define ENGINE_LOGIC_LOGIC_INC_RAY_H_

#include "vector3.h"

class ray {
 public:
  ray();
  ray(const point3& origin, const vec3& direction);

  point3 origin() const;
  vec3 direction() const;

  point3 at(double t) const;

  ~ray();
 public:
  point3 orig;
  vec3 dir;
};

#endif //ENGINE_LOGIC_LOGIC_INC_RAY_H_
