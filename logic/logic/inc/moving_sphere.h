//
// Created by Георгий Кузнецов on 02.06.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_MOVING_SPHERE_H_
#define ENGINE_LOGIC_LOGIC_INC_MOVING_SPHERE_H_

#include "resources.h"

class moving_sphere : public hittable {
 public:
  moving_sphere() = default;
  moving_sphere(const point3&, const point3&, double, double, double, std::shared_ptr<material>);

  virtual bool hit(const ray&, double t_min, double t_max, hit_record&) const;
  point3 center(double time) const;

 private:
  point3 pos_start, pos_end;
  double time_start, time_end;
  double radius;
  std::shared_ptr<material> mat_ptr;
};

#endif //ENGINE_LOGIC_LOGIC_INC_MOVING_SPHERE_H_
