//
// Created by Георгий Кузнецов on 24.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_SPHERE_H_
#define ENGINE_LOGIC_LOGIC_INC_SPHERE_H_

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
 public:
  sphere();

  sphere(const point3& cntr, double r, std::shared_ptr<material> m);

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

  ~sphere();

 public:
  point3 center_ = {0, 0, 0};
  double radius_ = 1;
  std::shared_ptr<material> mat_ptr;
};

#endif //ENGINE_LOGIC_LOGIC_INC_SPHERE_H_
