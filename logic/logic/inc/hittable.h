//
// Created by Георгий Кузнецов on 24.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_HITTABLE_H_
#define ENGINE_LOGIC_LOGIC_INC_HITTABLE_H_

#include "ray.h"
#include "vec3.h"

struct hit_record {
  // point of intersection
  point3 p;
  // normal in the intersection
  vec3 normal;
  // the root of the equation
  double t;
  // is it facing front
  bool front_face;
  // set if normal is front or outwards
  inline void set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal :-outward_normal;
  }
};

class hittable {
 public:
  // hit function that objects will override
  // t_min and t_max - parameters of the roots (borders of the acceptable roots)
  // rec - structure with all information of hitting an object
  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif //ENGINE_LOGIC_LOGIC_INC_HITTABLE_H_
