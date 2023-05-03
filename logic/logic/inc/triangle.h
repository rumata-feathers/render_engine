//
// Created by Георгий Кузнецов on 24.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_TRIANGLE_H_
#define ENGINE_LOGIC_LOGIC_INC_TRIANGLE_H_

#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
 public:
  triangle();

  triangle(const point3& v0, const point3& v1, const point3& v2);

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

  ~triangle();

 public:
  point3 v0;
  point3 v1;
  point3 v2;
};

#endif //ENGINE_LOGIC_LOGIC_INC_TRIANGLE_H_
