//
// Created by Георгий Кузнецов on 24.04.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_HITTABLE_LIST_H_
#define ENGINE_LOGIC_LOGIC_INC_HITTABLE_LIST_H_

#include "hittable.h"

class hittable_list : public hittable {
 public:
  hittable_list();
  hittable_list(std::shared_ptr<hittable> object);

  void clear();
  void add(std::shared_ptr<hittable> object);

  virtual bool hit(
      const ray& r, double t_min, double t_max, hit_record& rec) const override;

 public:
  std::vector<std::shared_ptr<hittable>> objects;
};

#endif //ENGINE_LOGIC_LOGIC_INC_HITTABLE_LIST_H_
