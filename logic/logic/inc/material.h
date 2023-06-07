//
// Created by Георгий Кузнецов on 14.05.2023.
//

#ifndef ENGINE_LOGIC_LOGIC_INC_MATERIAL_H_
#define ENGINE_LOGIC_LOGIC_INC_MATERIAL_H_
#include "resources.h"
//struct hit_record;
#include "hittable.h"

class material {
 public:
  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
                      ) const = 0;
  virtual bool read_mtl(){}

};
class BSDF : public material {
 public:
  BSDF(const color& a, float d) : albedo(a), diffuse(d) {}
  BSDF(const color& a, float d, float m) : albedo(a), metallic(m), diffuse(d) {}
  BSDF(const color& a, float d, float m, float f)
      : albedo(a), metallic(m), diffuse(d), metallic_roughness(f < 1 ? f : 1) {}
  BSDF(const color& a, float d, float m, float f, float gl, float i_r = 1.33, const color& gl_col = {1.0, 1.0, 1.0})
      : albedo(a),
        metallic(m),
        diffuse(d),
        metallic_roughness(f < 1 ? f : 1),
        glossiness(gl),
        ir(i_r),
        glass_colour(gl_col) {}

  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

 public:
  float diffuse = 1.0f;
  float metallic = 0;
  float metallic_roughness = 0;
  float ir = 1.33f;
  float glossiness = 0;
  color glass_colour = {1.0, 1.0, 1.0};
  color albedo;
 private:
  static double reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
  }
};


#endif //ENGINE_LOGIC_LOGIC_INC_MATERIAL_H_
