//
// Created by Георгий Кузнецов on 14.05.2023.
//

#include "../inc/material.h"
float sum_params() {
  return 0;
}
template<typename Number, typename ... Numbers>
float sum_params(const Number& number, const Numbers& ... rest) {
  return number + sum_params(rest...);
}

template<typename ... Numbers>
float unit_coef(const Numbers& ... args) {
  return float(1) / sum_params(args...);
}

bool BSDF::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
//  compute reflection
  auto reflected_direction =
      reflect(unit_vector(r_in.direction()), rec.normal) + metallic_roughness * random_in_unit_sphere();

  // compute diffuse
  auto diffuse_direction = rec.normal + random_unit_vector();
  {
    // Catch degenerate scatter direction
    if (diffuse_direction.near_zero()) {
      diffuse_direction = rec.normal;
    }
  }


  //compute glass
  vec3 glass_direction;
  {
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
    vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
      glass_direction = reflect(unit_direction, rec.normal);
    else
      glass_direction = refract(unit_direction, rec.normal, refraction_ratio);
  }

  // sum everything up;
  auto new_ray = reflected_direction * metallic + diffuse_direction * diffuse + glass_direction * glossiness;
  new_ray = unit_vector(new_ray);
  scattered = ray(rec.p, new_ray, r_in.get_time());
  //compute color
  auto color_coef = unit_coef(diffuse, glossiness, metallic);
  attenuation = albedo * diffuse * color_coef + glass_colour * glossiness * color_coef + albedo * metallic * color_coef;
  return true;
}
